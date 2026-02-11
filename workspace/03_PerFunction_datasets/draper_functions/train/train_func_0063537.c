clause_simplify(solver* s, clause* c)
{
    lit*   lits   = clause_begin(c);
    lbool* values = s->assigns;
    int i;

    assert(solver_dlevel(s) == 0);

    for (i = 0; i < clause_size(c); i++){
        lbool sig = !lit_sign(lits[i]); sig += sig - 1;
        if (values[lit_var(lits[i])] == sig)
            return l_True;
    }
    return l_False;
}
