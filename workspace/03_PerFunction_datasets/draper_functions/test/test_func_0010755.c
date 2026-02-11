calcVerticalMargins()
{
    if( isTableCell() ) {

	m_marginTop = TABLECELLMARGIN;
	m_marginBottom = TABLECELLMARGIN;
	return;
    }

    Length tm = style()->marginTop();
    Length bm = style()->marginBottom();


    int cw = containingBlock()->contentWidth();

    m_marginTop = tm.minWidth(cw);
    m_marginBottom = bm.minWidth(cw);
}
