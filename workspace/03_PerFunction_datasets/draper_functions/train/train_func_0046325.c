rt_dumplevel(dumpfile_t *hdr)
{
    if (TAPE_HEADER(hdr)) {
	hdr->dumplevel = 0;
	if (!PREV_RT(hdr)) return 0;
    } else {
	hdr->dumplevel = 0;
	if (!PREV_RT(hdr)) return 0;
	hdr->dumplevel = 1;
	if (!PREV_RT(hdr)) return 0;
    }
    return 1;
#undef PREV_RT
#define PREV_RT rt_dumplevel
}
