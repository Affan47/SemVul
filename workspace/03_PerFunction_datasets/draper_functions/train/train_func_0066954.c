make_stasche_localize_dlg_info(const Stasche_localize_tlg_info *tlg_info,
                               const int dlg_tag)
{
    Stasche_localize_dlg_info *dlg_info;
    int array_num;
    int i;

    if (tlg_info == NULL) return NULL;

    array_num = tlg_info->array_num;
    dlg_info = get_stasche_localize_dlg_info(array_num);

    dlg_info->dlg_tag = dlg_tag;
    dlg_info->tlg_info = tlg_info;
    for (i = 0; i <= array_num; i++) {
        Stasche_localize_array_info *array_info;

        array_info = make_stasche_localize_array_info(dlg_info, i);
        dlg_info->array_info[i] = array_info;
    }

    return dlg_info;
}
