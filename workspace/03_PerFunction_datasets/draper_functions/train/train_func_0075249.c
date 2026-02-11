_e_desktop_edit_free(E_Desktop_Edit *editor)
{
   if (!editor) return;
   E_OBJECT_CHECK(editor);
   E_OBJECT_TYPE_CHECK(editor, E_EAP_EDIT_TYPE);

   IFFREE(editor->tmp_image_path);
   E_FREE(editor);
}
