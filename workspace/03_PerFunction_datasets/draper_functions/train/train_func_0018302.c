on_send_widget_to_shell_activate(GtkWidget *menuitem,
                                 ParasiteWindow *parasite)
{
    GtkWidget *widget = parasite_widget_tree_get_selected_widget(
        PARASITE_WIDGET_TREE(parasite->widget_tree));
    if (widget != NULL) {
        char *str = g_strdup_printf("parasite.gobj(%p)", widget);

        parasite_python_shell_append_text(
            PARASITE_PYTHON_SHELL(parasite->python_shell),
            str, NULL);

        g_free(str);
        parasite_python_shell_focus(PARASITE_PYTHON_SHELL(parasite->python_shell));
    }
}
