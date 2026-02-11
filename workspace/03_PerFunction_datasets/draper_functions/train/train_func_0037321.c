_e_main_efreet_paths_init(void)
{
   Eina_List **list;

   if ((list = efreet_icon_extra_list_get()))
     {
        char buff[PATH_MAX];

        e_user_dir_concat_static(buff, "icons");
        *list = eina_list_prepend(*list, (void *)eina_stringshare_add(buff));
        e_prefix_data_concat_static(buff, "data/icons");
        *list = eina_list_prepend(*list, (void *)eina_stringshare_add(buff));
     }
}
