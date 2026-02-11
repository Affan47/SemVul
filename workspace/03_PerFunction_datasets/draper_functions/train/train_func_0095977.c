get_module_info_list(Module_table *module_head)
{
    Module_table **ma;
    List *module_info_list;
    List *list = NULL;
    int nma, i, total_acc;

    ma = get_sorted_module_array(module_head, &nma);

    total_acc = (acc_stasche_head != NULL) ?
        acc_stasche_head->acc_num : 0;

    for (i = nma - 1; i >= 0; i--) {
        if (ma[i]->kind != MODULE_BLOCKDATA) {
            Block_info *block_info_head;
            int total_pe = ma[i]->super_hmdf->pe_num;

            block_info_head = get_block_info(ma[i]->block_head,
                                             list);

            list = list_append(list,
                               module_info_new(ma[i]->entry,
                                               ma[i]->kind,
                                               total_pe,
                                               total_acc,
                                               block_info_head,
                                               NULL,
                                               ma[i]));

            if (info_fp != NULL) {
#ifdef WRITE_PATH
                print_path_layer(block_info_head);
#endif
            }
        }
    }

    module_info_list = list_reverse(list);
    list_free(list);

    return module_info_list;
}
