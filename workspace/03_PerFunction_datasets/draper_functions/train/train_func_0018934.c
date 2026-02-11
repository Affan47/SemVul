findCCSMaxLens(CostCentreStack *ccs, nat indent, nat *max_label_len, nat *max_module_len) {
    CostCentre *cc;
    IndexTable *i;

    cc = ccs->cc;

    *max_label_len = stg_max(*max_label_len, indent + strlen_utf8(cc->label));
    *max_module_len = stg_max(*max_module_len, strlen_utf8(cc->module));

    for (i = ccs->indexTable; i != 0; i = i->next) {
        if (!i->back_edge) {
            findCCSMaxLens(i->ccs, indent+1, max_label_len, max_module_len);
        }
    }
}
