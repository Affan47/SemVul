DelBufMark(b, m)
Buffer	*b;
register Mark	*m;
{
	register Mark	*mp = b->b_marks;

	if (MarkHighlighting)
		makedirty(m->m_line);
	if (m == mp)
		b->b_marks = m->m_next;
	else {
		while (mp != NULL && mp->m_next != m)
			mp = mp->m_next;
		if (mp == NULL)
			complain("Unknown mark!");
		mp->m_next = m->m_next;
	}
	RecycleMark(m);
}
