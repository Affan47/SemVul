do_msghash_line(struct msghashinfo *p, const char *l)
{
unsigned long ll;

	if (*l == 0)	return;
	ll=strlen(l);

	if (p->numlines <= MSGHASH_HIMARGIN)

	{
		md5_context_hashstream(&p->c_entire, l, ll);
		p->c_entire_cnt += ll;
	}

	if (p->numlines++ < MSGHASH_MARGIN)
	{
		strcpy(p->linebuf[p->linebuf_head], l);
		p->linebuf_head= (p->linebuf_head+1) % MSGHASH_MARGIN;
	}
	else
	{
	const char *s=p->linebuf[p->linebuf_tail];
	unsigned long sl=strlen(s);

		md5_context_hashstream(&p->c_top, s, sl);
		p->c_top_cnt += sl;

		strcpy(p->linebuf[p->linebuf_head], l);
		p->linebuf_head= (p->linebuf_head+1) % MSGHASH_MARGIN;
		p->linebuf_tail= (p->linebuf_tail+1) % MSGHASH_MARGIN;

		md5_context_hashstream(&p->c_bot, l, ll);
		p->c_bot_cnt += ll;
	}
}
