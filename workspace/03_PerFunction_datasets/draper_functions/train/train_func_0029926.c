changeThickness()
{
	if (changeThickness(m_holeSettings, sender())) {
		QLineEdit * edit = qobject_cast<QLineEdit *>(sender());
		changeHoleSize(m_holeSettings.holeDiameter + "," + edit->text() + m_holeSettings.currentUnits());
	}
}
