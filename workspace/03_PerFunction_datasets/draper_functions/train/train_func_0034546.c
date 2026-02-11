c_alpha_equal(const gs_composite_t * pcte, const gs_composite_t * pcte2)
{
    return (pcte2->type == pcte->type &&
#define pacte2 ((const gs_composite_alpha_t *)pcte2)
            pacte2->params.op == pacte->params.op &&
            (pacte->params.op != composite_Dissolve ||
             pacte2->params.delta == pacte->params.delta));
#undef pacte2
}
