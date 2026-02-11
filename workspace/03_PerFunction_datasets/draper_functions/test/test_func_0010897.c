msghash_finish(struct msghashinfo *p)
{
	if (p->numlines < MSGHASH_HIMARGIN)
	{
		memcpy(&p->c_top, &p->c_entire, sizeof(p->c_top));
		p->c_top_cnt=p->c_entire_cnt;

		memcpy(&p->c_bot, &p->c_entire, sizeof(p->c_bot));
		p->c_bot_cnt=p->c_entire_cnt;
	}

	md5_context_endstream(&p->c_top, p->c_top_cnt);
	md5_context_endstream(&p->c_bot, p->c_bot_cnt);

	md5_context_digest(&p->c_top, p->md1);
	md5_context_digest(&p->c_bot, p->md2);
}
