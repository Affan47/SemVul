setup_root_args(char *args)
{
	char *buf, *dst, *sep;

	if (!args)
		return kstrdup("subvolid=0", GFP_NOFS);


	buf = dst = kmalloc(strlen(args) + strlen(",subvolid=0") + 1, GFP_NOFS);
	if (!buf)
		return NULL;

	while (1) {
		sep = strchrnul(args, ',');
		if (!strstarts(args, "subvol=") &&
		    !strstarts(args, "subvolid=")) {
			memcpy(dst, args, sep - args);
			dst += sep - args;
			*dst++ = ',';
		}
		if (*sep)
			args = sep + 1;
		else
			break;
	}
	strcpy(dst, "subvolid=0");

	return buf;
}
