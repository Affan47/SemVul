insert (ichar_t *word)
{
    register int	i;
    register char *	realword;

    realword = ichartosstr (word, 0);
    for (i = 0; i < m_pcount; i++)
	{
		if (strcmp (m_possibilities[i], realword) == 0)
			return (0);
	}

    strcpy (m_possibilities[m_pcount++], realword);
    i = strlen (realword);
    if (i > m_maxposslen)
		m_maxposslen = i;
    if (m_pcount >= MAXPOSSIBLE)
		return (-1);
    else
		return (0);
}
