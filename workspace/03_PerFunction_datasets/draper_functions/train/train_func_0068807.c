makeDefaultConfig(void)
{
    Section *cs, **csp;
    Entry *ce, **cep;
    int sc, ec;

    for (csp = &config, sc = 0; sc < as(dAllSects); csp = &(cs->next), sc++) {
        cs = mcalloc(sizeof(*cs));
        *csp = cs;
        cs->spec = findSect(dAllSects[sc].name);
        cs->name = dAllSects[sc].name;
        cs->comment = dAllSects[sc].comment;
        for (cep = &(cs->ents), ec = 0; ec < dAllSects[sc].nents;
             cep = &(ce->next), ec++)
        {
            ce = mcalloc(sizeof(*ce));
            *cep = ce;
            ce->spec = findEnt(cs->spec, dAllSects[sc].ents[ec].key);
            ce->value = dAllSects[sc].ents[ec].value;
            ce->active = dAllSects[sc].ents[ec].active;
        }
    }
}
