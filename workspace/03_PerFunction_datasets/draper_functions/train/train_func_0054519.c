seen_ltexcl(struct htmlfilter_info *p,
			  const unicode_char *uc,
			  size_t cnt)
{
	if (*uc == '-')
	{


		p->handler_func=seen_comment;

		return seen_comment(p, uc, cnt);
	}

	p->handler_func=seen_sgentity;
	return seen_sgentity(p, uc, cnt);
}
