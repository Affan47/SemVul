get_phrase_query(QParser *qp, char *field,
                               Phrase *phrase, char *slop_str)
{
    const int pos_cnt = phrase->size;
    Query *q = NULL;

    if (pos_cnt == 1) {
        char **words = phrase->positions[0].terms;
        const int word_count = ary_size(words);
        if (word_count == 1) {
            q = get_term_q(qp, field, words[0]);
        }
        else {
            int i;
            q = bq_new(false);
            for (i = 0; i < word_count; i++) {
                bq_add_query_nr(q, get_term_q(qp, field, words[i]), BC_SHOULD);
            }
        }
    }
    else if (pos_cnt > 1) {
        Token *token;
        TokenStream *stream;
        int i, j;
        int pos_inc = 0;
        q = phq_new(field);
        if (slop_str) {
            int slop;
            sscanf(slop_str,"%d",&slop);
            ((PhraseQuery *)q)->slop = slop;
        }

        for (i = 0; i < pos_cnt; i++) {
            char **words = phrase->positions[i].terms;
            const int word_count = ary_size(words);
            if (pos_inc) {
                ((PhraseQuery *)q)->slop++;
            }
            pos_inc += phrase->positions[i].pos + 1;

            if (word_count == 1) {
                stream = get_cached_ts(qp, field, words[0]);
                while ((token = ts_next(stream))) {
                    if (token->pos_inc) {
                        phq_add_term(q, token->text,
                                     pos_inc ? pos_inc : token->pos_inc);
                    }
                    else {
                        phq_append_multi_term(q, token->text);
                        ((PhraseQuery *)q)->slop++;
                    }
                    pos_inc = 0;
                }
            }
            else {
                bool added_position = false;

                for (j = 0; j < word_count; j++) {
                    stream = get_cached_ts(qp, field, words[j]);
                    if ((token = ts_next(stream))) {
                        if (!added_position) {
                            phq_add_term(q, token->text,
                                         pos_inc ? pos_inc : token->pos_inc);
                            added_position = true;
                            pos_inc = 0;
                        }
                        else {
                            phq_append_multi_term(q, token->text);
                        }
                    }
                }
            }
        }
    }
    return q;
}
