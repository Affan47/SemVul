e_int_config_tiling_module(E_Container *con,
                           const char  *params __UNUSED__)
{
    E_Config_Dialog *cfd;
    E_Config_Dialog_View *v;
    char buf[PATH_MAX];

    if (e_config_dialog_find("E", "windows/tiling"))
        return NULL;

    v = E_NEW(E_Config_Dialog_View, 1);

    v->create_cfdata = _create_data;
    v->free_cfdata = _free_data;
    v->basic.apply_cfdata = _basic_apply_data;
    v->basic.create_widgets = _basic_create_widgets;

    snprintf(buf, sizeof(buf), "%s/e-module-tiling.edj",
             e_module_dir_get(tiling_g.module));
    cfd = e_config_dialog_new(con,
                              _("Tiling Configuration"),
                              "E", "windows/tiling",
                              buf, 0, v, NULL);
    return cfd;
}
