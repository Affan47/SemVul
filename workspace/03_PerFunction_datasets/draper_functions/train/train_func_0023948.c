fetch_file(const unsigned char *sha1)
{
	static int object_name_start = -1;
	static char filename[PATH_MAX];
	char *hex = sha1_to_hex(sha1);
	char *dest_filename = sha1_file_name(sha1);

	if (object_name_start < 0) {
		strcpy(filename, path);
		strcat(filename, "/objects/");
		object_name_start = strlen(filename);
	}
	filename[object_name_start+0] = hex[0];
	filename[object_name_start+1] = hex[1];
	filename[object_name_start+2] = '/';
	strcpy(filename + object_name_start + 3, hex + 2);
	return copy_file(filename, dest_filename, hex, 0);
}
