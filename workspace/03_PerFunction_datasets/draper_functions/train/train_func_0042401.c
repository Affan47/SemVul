overwrite_contexts(reaching_context_t& C1, reaching_context_t& C2)
{

    reaching_context_t::iterator I;
    for(I=C2.begin(); I!=C2.end(); I++)
    {
        gm_symtab_entry* sym = I->first;
        gm_rda_set& S = I->second;

        C1[sym] = S;
    }
}
