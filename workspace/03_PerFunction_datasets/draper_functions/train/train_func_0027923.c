fm_folder_get_file_by_name(FmFolder* folder, const char* name)
{
    FmPath *path = fm_path_new_child(folder->dir_path, name);
    GList* l = _fm_folder_get_file_by_path(folder, path);
    fm_path_unref(path);
    return l ? (FmFileInfo*)l->data : NULL;
}
