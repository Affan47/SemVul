abi_widget_new_with_file (const gchar * file)
{
	AbiWidget * abi;

	UT_return_val_if_fail (file != 0, 0);

	abi = static_cast<AbiWidget *>(g_object_new (abi_widget_get_type (), NULL));
	abi_widget_construct (abi, file);

	return GTK_WIDGET (abi);
}
