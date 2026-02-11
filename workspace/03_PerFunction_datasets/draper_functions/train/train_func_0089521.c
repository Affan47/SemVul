Layout_Row_info(Layout_Row *row, C4_Model *model){
    register gint i;
    g_print("Layout_Cell count: [%d]\n", row->cell_list->len);
    for(i = 0; i < row->cell_list->len; i++){
        g_print("Layout_Cell [%d]:\n", i);
        Layout_Cell_info(row->cell_list->pdata[i], model);
        }
    return;
    }
