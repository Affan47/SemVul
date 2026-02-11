destruct_tlg_dlg_car_layer(TlgDlgCarLayer *layer)
{
    List *li, *temp;

    temp = layer->order_tdcn;

    for (li = temp; li != NULL; li = li->next) {
        TlgDlgCarNode *tdcn = li->data;
        if (tdcn != NULL) {
            destruct_tlg_dc_node(li->data);
        }
    }

    list_free(layer->order_tdcn);
    layer->order_tdcn = NULL;
    free(layer);
}
