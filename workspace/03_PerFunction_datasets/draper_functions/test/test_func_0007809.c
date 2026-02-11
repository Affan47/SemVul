e_source_mail_signature_symlink_sync (ESource *source,
                                      const gchar *symlink_target,
                                      GCancellable *cancellable,
                                      GError **error)
{
	ESourceMailSignature *extension;
	const gchar *extension_name;
	GFile *file;

	g_return_val_if_fail (E_IS_SOURCE (source), FALSE);
	g_return_val_if_fail (symlink_target != NULL, FALSE);

	extension_name = E_SOURCE_EXTENSION_MAIL_SIGNATURE;
	extension = e_source_get_extension (source, extension_name);
	file = e_source_mail_signature_get_file (extension);


	g_file_delete (file, cancellable, NULL);

	return g_file_make_symbolic_link (
		file, symlink_target, cancellable, error);
}
