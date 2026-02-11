mock_C_DestroyObject (CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject)
{
  GPkcs11Array *attrs;
  Session *session;
  gboolean priv;

  session = g_hash_table_lookup (the_sessions, GUINT_TO_POINTER (hSession));
  g_return_val_if_fail (session, CKR_SESSION_HANDLE_INVALID);

  attrs = lookup_object (session, hObject);
  g_return_val_if_fail (attrs, CKR_OBJECT_HANDLE_INVALID);

  if (g_pkcs11_array_find_boolean (attrs, CKA_PRIVATE, &priv) && priv)
    {
      if (!logged_in)
        return CKR_USER_NOT_LOGGED_IN;
    }

  g_hash_table_remove (the_objects, GUINT_TO_POINTER (hObject));
  g_hash_table_remove (session->objects, GUINT_TO_POINTER (hObject));

  return CKR_OK;
}
