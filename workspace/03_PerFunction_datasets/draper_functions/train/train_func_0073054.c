check_dep_among_dc_tdcn(TlgDlgCarNode *tdcn)
{
    return (test_and_IntSet(tdcn->pred, tdcn->inner)
            || test_and_IntSet(tdcn->succ, tdcn->inner));
}
