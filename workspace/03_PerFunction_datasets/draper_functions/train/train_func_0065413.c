jl_tuple_subtype_(jl_value_t **child, size_t cl,
                             jl_value_t **parent, size_t pl, int ta,
                             int morespecific, int invariant)
{
    size_t ci=0, pi=0;
    int mode = 0;
    while(1) {
        int cseq = !ta && (ci<cl) && jl_is_seq_type(child[ci]);
        int pseq = (pi<pl) && jl_is_seq_type(parent[pi]);
        if ((!morespecific||mode) && cseq && !pseq)
            return mode;
        if (ci >= cl)
            return (pi>=pl || pseq);
        if (pi >= pl)
            return 0;
        jl_value_t *ce = child[ci];
        jl_value_t *pe = parent[pi];
        if (cseq) ce = jl_tparam0(ce);
        if (pseq) pe = jl_tparam0(pe);

        if (!jl_subtype_le(ce, pe, ta, morespecific, invariant))
            return 0;

        if (morespecific) {

            if (!(jl_types_equal(ce,pe) ||
                  (jl_is_typevar(pe) &&
                   jl_types_equal(ce,((jl_tvar_t*)pe)->ub)))) {
                mode = 1;
                assert(!ta);


            }
        }

        if (cseq && pseq) return 1;
        if (!cseq) ci++;
        if (!pseq) pi++;
    }
    return 0;
}
