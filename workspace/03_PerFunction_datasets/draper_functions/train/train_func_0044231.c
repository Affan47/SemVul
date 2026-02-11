join_path_components(char *ret_path,
					 const char *head, const char *tail)
{
	if (ret_path != head)
		strlcpy(ret_path, head, MAXPGPATH);


	while (tail[0] == '.' && IS_DIR_SEP(tail[1]))
		tail += 2;

	if (*tail)
	{

		snprintf(ret_path + strlen(ret_path), MAXPGPATH - strlen(ret_path),
				 "%s%s",
				 (*(skip_drive(head)) != '\0') ? "/" : "",
				 tail);
	}
}
