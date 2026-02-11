get_stasche_localize_tlg_info(const int dlg_num,
                              const int array_num,
                              const int block_num)
{
    Stasche_localize_tlg_info *tlg_info;

    tlg_info = calloc(1, sizeof(Stasche_localize_tlg_info));
    if (tlg_info == NULL) {
        fatal("No room!!\n");
    }

    construct_IntSet(tlg_info->localize_entry, array_num + 1);

    tlg_info->dlg_info
        = calloc(dlg_num + 1, sizeof(Stasche_localize_dlg_info*));
    tlg_info->car_info
        = calloc(block_num + 1, sizeof(Stasche_localize_car_info*));
    if (tlg_info->dlg_info == NULL || tlg_info->car_info == NULL) {
        fatal("No room!!\n");
    }

    return tlg_info;
}
