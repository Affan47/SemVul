default_pos_tagger(cst_utterance *u)
{
    cst_item *word;
    const cst_val *p;
    const cst_cart *tagger;

    p = get_param_val(u->features,"pos_tagger_cart",NULL);
    if (p == NULL)
        return u;
    tagger = val_cart(p);

    for (word=relation_head(utt_relation(u,"Word"));
	 word; word=item_next(word))
    {
        p = cart_interpret(word,tagger);
        item_set_string(word,"pos",val_string(p));
    }

    return u;
}
