lookup_object (Session *session,
               CK_OBJECT_HANDLE hObject)
{
  GPkcs11Array *attrs;
  attrs = g_hash_table_lookup (the_objects, GUINT_TO_POINTER (hObject));
  if (!attrs)
    attrs = g_hash_table_lookup (session->objects, GUINT_TO_POINTER (hObject));
  return attrs;
}
