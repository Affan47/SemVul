gui_tree_display(tree_info_t* info, gboolean destroy_old, gboolean new_history)
{
    if (destroy_old)
    {
        if (CurrentItem)
        {
            while (CurrentItem->parent) CurrentItem = CurrentItem->parent;
            tree_destroy(CurrentItem->node);
            tree_info_destroy(CurrentItem);
        }
        CurrentItem = NULL;
        history_clear();
    }


    if (CurrentItem != info)
    {
        if (new_history) history_append(info);
        CurrentItem = info;
        gui_paths_update();
    }

    gui_tree_evaluate(info);
    gui_tree_show(info);
    gui_show_pix(Area);

    gui_buttons_update();

    {
        char* temp1 = print_filesize(info->node->size);
        char* temp2 = g_strdup_printf("<b>%s</b>", temp1);
        gtk_label_set_markup(SizeLabel, temp2);
        g_free(temp1);
        g_free(temp2);
    }

}
