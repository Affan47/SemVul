_g_file_equal (GFile *file1,
	       GFile *file2)
{
	if ((file1 == NULL) && (file2 == NULL))
		return TRUE;
	if ((file1 == NULL) || (file2 == NULL))
		return FALSE;

	return g_file_equal (file1, file2);
}
