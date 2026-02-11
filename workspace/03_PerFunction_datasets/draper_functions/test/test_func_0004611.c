get_layer_info(Block *block, List *module_info_list, int total_iter)
{
    Layer_info *layer_info;

    if (is_static_layer_for_fv_control(block)) {
        if (block->hmdf != NULL)
            layer_info = get_layer_info_for_static_hmdf(block,
                                                        module_info_list,
                                                        total_iter);
        else
            layer_info = get_layer_info_for_static_flow(block,
                                                        module_info_list,
                                                        total_iter);

    } else {
        layer_info = get_layer_info_for_dynamic(block,
                                                module_info_list,
                                                total_iter);
    }

    return layer_info;
}
