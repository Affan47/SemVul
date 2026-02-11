PopMark()
{
	int	pmark;

	if (curmark == NULL)
		return;

	ExchPtMark();
	pmark = curbuf->b_themark;
	do {
		if (--pmark < 0)
			pmark = NMARKS - 1;
	} while (curbuf->b_markring[pmark] == NULL);
	curbuf->b_themark = pmark;
	if (MarkHighlighting)
		makedirty(curmark->m_line);
}
