_e_wid_fprev_preview_fm(E_Widget_Data *wd)
{
   E_Fm2_Config fmc;
   Evas_Object *o;
   int mw;

   if (!wd->is_dir) return;
   if (!wd->path) return;
   if (wd->o_preview_preview && (!wd->prev_is_fm))
     {
        evas_object_del(wd->o_preview_preview);
        wd->o_preview_preview = NULL;
     }
   if (!wd->o_preview_preview)
     {
        Evas *evas;

        evas = evas_object_evas_get(wd->obj);
        o = e_fm2_add(evas);
        wd->o_preview_preview = o;
        wd->prev_is_fm = EINA_TRUE;
        memset(&fmc, 0, sizeof(E_Fm2_Config));
        fmc.view.mode = E_FM2_VIEW_MODE_LIST;
        fmc.view.open_dirs_in_place = 1;
        fmc.view.selector = 1;
        fmc.view.single_click = 0;
        fmc.view.no_subdir_jump = 1;
        fmc.view.no_subdir_drop = 1;
        fmc.view.link_drop = 1;
        fmc.icon.list.w = 24;
        fmc.icon.list.h = 24;
        fmc.icon.fixed.w = 1;
        fmc.icon.fixed.h = 1;
        fmc.list.sort.no_case = 1;
        fmc.view.no_click_rename = 1;
        fmc.selection.single = 1;
        e_fm2_config_set(o, &fmc);
        e_fm2_icon_menu_flags_set(o, E_FM2_MENU_NO_VIEW_MENU);
        evas_object_smart_callback_add(o, "dir_changed",
                                       _e_wid_cb_dir_changed, wd->obj);
        evas_object_smart_callback_add(o, "selection_change",
                                       _e_wid_cb_selection_change, wd->obj);
        evas_object_smart_callback_add(o, "changed",
                                       _e_wid_cb_changed, wd->obj);
        evas_object_smart_callback_add(o, "files_deleted",
                                       _e_wid_cb_file_deleted, wd->obj);
        evas_object_smart_callback_add(o, "selected",
                                       _e_wid_cb_selected, wd->obj);
        o = e_widget_scrollframe_pan_add(evas, wd->o_preview_preview,
                                         e_fm2_pan_set,
                                         e_fm2_pan_get,
                                         e_fm2_pan_max_get,
                                         e_fm2_pan_child_size_get);
        wd->o_preview_scrollframe = o;
        e_widget_size_min_get(wd->o_preview_list, &mw, NULL);

        e_widget_size_min_set(o, 0, wd->h);
        evas_object_propagate_events_set(wd->o_preview_preview, 0);
        e_widget_scrollframe_focus_object_set(o, wd->o_preview_preview);
        e_widget_table_object_append(wd->o_preview_preview_table,
                                     o, 0, 0, 2, 1, 1, 1, 1, 1);
        e_widget_list_object_repack(wd->o_preview_list,
                                    wd->o_preview_preview_table,
                                    1, 1, 0.5);
        e_widget_list_object_repack(wd->o_preview_list,
                                    wd->o_preview_properties_table,
                                    1, 1, 0.5);
     }
   e_fm2_path_set(wd->o_preview_preview, "/", wd->path);
}
