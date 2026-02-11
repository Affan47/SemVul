quick_open_plugin_project_added(QuickOpenPlugin* self, IAnjutaProject* project)
{
    AnjutaProjectNode* root;
    GFile* project_root;

    root = ianjuta_project_get_root(project, NULL);
    project_root = anjuta_project_node_get_file(root);
    quick_open_dialog_set_project_root(self->dialog, project_root);

    if (ianjuta_project_is_loaded(project, NULL))
        quick_open_plugin_load_project_files(self, project);
}
