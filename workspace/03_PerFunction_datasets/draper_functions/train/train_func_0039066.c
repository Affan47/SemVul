gwy_resource_editor_editor_closed(GwyResourceEditor *editor)
{
    gwy_resource_editor_commit(editor);
    g_assert(editor->edited_resource);

    g_string_free(editor->edited_resource, TRUE);
    editor->edited_resource = NULL;
    editor->edit_window = NULL;
}
