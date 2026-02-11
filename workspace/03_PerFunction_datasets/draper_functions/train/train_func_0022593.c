init(const QString &name)
{
	if (!name.isEmpty())
		setObjectName(name);

	m_selectCombo = new QComboBox;
	setDefaultWidget(m_selectCombo);
	connect(m_selectCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setCurrentItem()));
}
