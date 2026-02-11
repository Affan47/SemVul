delete_inner_tdcn(TlgDlgCarNode *tdcn)
{
    DlgCarNode *dcn;
    List *li;

    for (li = tdcn->dlg_car_nodes; li != NULL; li = li->next) {
        dcn = li->data;
        subtract_IntSet(tdcn->pred, tdcn->pred, dcn->inner);
        subtract_IntSet(tdcn->succ, tdcn->succ, dcn->inner);
    }
}
