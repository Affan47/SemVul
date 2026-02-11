cancelEditing()
{
	bool check = false;
	foreach (Timer* timer, m_timers) {
		check |= timer->isEditing();
	}
	if (check) {
		if (QMessageBox::question(this, tr("Question"), tr("Cancel editing timers?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::No) {
			return false;
		} else {
			foreach (Timer* timer, m_timers) {
				timer->cancelEditing();
			}
		}
	}
	return true;
}
