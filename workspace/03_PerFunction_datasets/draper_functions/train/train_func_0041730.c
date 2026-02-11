strbuf_fgets(STRBUF *sb, FILE *ip, int flags)
{
	if (!(flags & STRBUF_APPEND))
		strbuf_reset(sb);

	if (sb->curp >= sb->endp)
		__strbuf_expandbuf(sb, EXPANDSIZE);
	if (sb->alloc_failed)
		return sb->sbuf;

	for (;;) {
		if (!fgets(sb->curp, sb->endp - sb->curp, ip)) {
			if (sb->curp == sb->sbuf)
				return NULL;
			break;
		}
		sb->curp += strlen(sb->curp);
		if (sb->curp > sb->sbuf && *(sb->curp - 1) == '\n')
			break;
		else if (feof(ip)) {
			return sb->sbuf;
		}
		__strbuf_expandbuf(sb, EXPANDSIZE);
		if (sb->alloc_failed)
			return sb->sbuf;
	}
	if (flags & STRBUF_NOCRLF) {
		if (*(sb->curp - 1) == '\n')
			*(--sb->curp) = 0;
		if (sb->curp > sb->sbuf && *(sb->curp - 1) == '\r')
			*(--sb->curp) = 0;
	}
	return sb->sbuf;
}
