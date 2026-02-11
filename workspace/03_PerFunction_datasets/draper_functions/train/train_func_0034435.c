inf_gtk_certificate_dialog_chain_data_func(GtkTreeViewColumn* column,
                                           GtkCellRenderer* renderer,
                                           GtkTreeModel* tree_model,
                                           GtkTreeIter* iter,
                                           gpointer user_data)
{
  gpointer crt_ptr;
  gnutls_x509_crt_t cert;
  GValue value = { 0 };
  gchar* common_name;

  gtk_tree_model_get(tree_model, iter, 0, &crt_ptr, -1);
  cert = (gnutls_x509_crt_t)crt_ptr;

  common_name =
    inf_cert_util_get_dn_by_oid(cert, GNUTLS_OID_X520_COMMON_NAME, 0);

  g_value_init(&value, G_TYPE_STRING);

  if(common_name != NULL)
    g_value_take_string(&value, common_name);
  else
    g_value_set_static_string(&value, _("<Unknown Certificate Holder>"));

  g_object_set_property(G_OBJECT(renderer), "text", &value);
  g_value_unset(&value);
}
