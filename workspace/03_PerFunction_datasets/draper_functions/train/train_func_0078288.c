getItemCount() const
{
	UT_return_val_if_fail(m_pDoc,0);
	return (m_pDoc->getRevisions()).getItemCount() + 1;
}
