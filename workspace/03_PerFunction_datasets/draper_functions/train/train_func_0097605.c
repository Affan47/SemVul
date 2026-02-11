clone_imagename(char *buf, size_t len, int clones)
{
	if (clones > 0)
		snprintf(buf, len, "%s-clone%d", iname, clones);
	else
		strncpy(buf, iname, len);
}
