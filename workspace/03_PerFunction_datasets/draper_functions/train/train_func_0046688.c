aim_oft_dirconvert_tostupid(char *name)
{
	while (name[0]) {
		if (name[0] == 0x01)
			name[0] = G_DIR_SEPARATOR;
		name++;
	}
}
