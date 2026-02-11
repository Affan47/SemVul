get_phrase_q(QParser *qp, Phrase *phrase, char *slop_str)
{
    Query *volatile q = NULL;
    FLDS(q, get_phrase_query(qp, field, phrase, slop_str));
    ph_destroy(phrase);
    return q;
}
