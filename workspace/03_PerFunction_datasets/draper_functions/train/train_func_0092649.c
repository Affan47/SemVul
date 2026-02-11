m_fch(m, cnt, key)
	MARK	m;
	long	cnt;
	char	key;
{
	REG char	*text;

	DEFAULT(1);

	prevfwdfn = m_fch;
	prevrevfn = m_Fch;
	prev_key = key;

	pfetch(markline(m));
	text = ptext + markidx(m);
	while (cnt-- > 0)
	{
		do
		{
			m++;
			text++;
		} while (*text && *text != key);
	}
	if (!*text)
	{
		return MARK_UNSET;
	}
	return m;
}
