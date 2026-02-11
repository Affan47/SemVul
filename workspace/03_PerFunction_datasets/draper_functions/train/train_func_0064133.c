trace_cachehdr(const char *name, const char *contents, void *rock)
{
    struct buf *buf = (struct buf *) rock;
    const char **hdr, *sensitive[] =
	{ "authorization", "cookie", "proxy-authorization", NULL };


    if (name[0] == ':') return;

    for (hdr = sensitive; *hdr && strcmp(name, *hdr); hdr++);

    if (!*hdr) buf_printf(buf, "%c%s: %s\r\n",
			  toupper(name[0]), name+1, contents);
}
