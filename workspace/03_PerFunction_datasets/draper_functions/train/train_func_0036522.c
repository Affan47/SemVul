pk_transaction_eula_required_cb (PkBackend *backend,
				 PkEulaRequired *item,
				 PkTransaction *transaction)
{
	gchar *eula_id;
	gchar *package_id;
	gchar *vendor_name;
	gchar *license_agreement;

	g_return_if_fail (PK_IS_TRANSACTION (transaction));
	g_return_if_fail (transaction->priv->tid != NULL);


	pk_results_add_eula_required (transaction->priv->results, item);


	g_object_get (item,
		      "eula-id", &eula_id,
		      "package-id", &package_id,
		      "vendor-name", &vendor_name,
		      "license-agreement", &license_agreement,
		      NULL);


	g_debug ("emitting eula-required %s, %s, %s, %s",
		   eula_id, package_id, vendor_name, license_agreement);
	g_dbus_connection_emit_signal (transaction->priv->connection,
				       NULL,
				       transaction->priv->tid,
				       PK_DBUS_INTERFACE_TRANSACTION,
				       "EulaRequired",
				       g_variant_new ("(ssss)",
						      eula_id,
						      package_id,
						      vendor_name != NULL ? vendor_name : "",
						      license_agreement != NULL ? license_agreement : ""),
				       NULL);


	transaction->priv->emit_eula_required = TRUE;

	g_free (eula_id);
	g_free (package_id);
	g_free (vendor_name);
	g_free (license_agreement);
}
