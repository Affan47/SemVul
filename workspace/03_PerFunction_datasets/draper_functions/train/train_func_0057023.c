make_cluster_info_from_ws(List *write_sharing_list, Cluster_info *ws_obj_info,
                          Cluster_info *wp_alias_info)
{
    List *li;
    Write_sharing *ws;

    ws_obj_info = construct_cluster_info(128, hash_func_module,
                                             clustering_by_wp_alias);
    for (li = write_sharing_list; li != NULL; li = li->next) {
        ws = li->data;
        cluster_add(ws_obj_info, ws, wp_alias_info);
    }
    dump_ws_obj_info(ws_obj_info);

    return ws_obj_info;
}
