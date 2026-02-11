selfdestruct(const bool &applyChanges)
{
	m_autodestroy = true;


	if (m_step != 0)
		return;

	if (applyChanges && wasChanged())
		apply();
	else
		deleteLater();
}
