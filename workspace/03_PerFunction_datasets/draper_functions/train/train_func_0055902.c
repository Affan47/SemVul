BUpList()
{
	register int	num = arg_value();
	Bufpos	*mp;

	if (num < 0) {
		negate_arg();
		FDownList();
	}
	while (--num >= 0) {
		mp = m_paren(')', BACKWARD, YES, YES);
		if (mp == NULL)
			mp_error();
		else
			SetDot(mp);
	}
}
