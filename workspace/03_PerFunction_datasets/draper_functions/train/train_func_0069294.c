_clean_page(BD_IG_PAGE *p)
{
    unsigned ii;

    _clean_effect_sequence(&p->in_effects);
    _clean_effect_sequence(&p->out_effects);

    for (ii = 0; ii < p->num_bogs; ii++) {
        _clean_bog(&p->bog[ii]);
    }
    X_FREE(p->bog);
}
