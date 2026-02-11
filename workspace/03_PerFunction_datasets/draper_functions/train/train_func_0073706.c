vm_delete(char *file)
{
	int res;

	ast_debug(1, "Deleting voicemail file %s\n", file);

	res = unlink(file);
	res |=  ast_filedelete(file, NULL);
	return res;
}
