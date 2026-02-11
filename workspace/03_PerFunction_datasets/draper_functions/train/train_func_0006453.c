UpdateDuration()
{
	TransferDataFromWindow();

	if( m_EndDateObj.Get() < m_StartDateObj.Get() ) {


		m_EndDateCtrl->SetValue(m_StartDateCtrl->GetValue());
		m_EndHoursSpinner->SetValue(m_StartHoursSpinner->GetValue());
		m_EndMinutesSpinner->SetValue(m_StartMinutesSpinner->GetValue());


		m_DurationHoursSpinner->SetValue(0);
		m_DurationMinutesSpinner->SetValue(0);
		return;
	}
	else {

		time_t diff = m_EndDateObj.Get() - m_StartDateObj.Get();
		diff /= 60;
		m_DurationHoursSpinner->SetValue(diff / 60);
		m_DurationMinutesSpinner->SetValue(diff % 60);
	}
}
