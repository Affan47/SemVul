openDosageDialog()
{
    if (m_CurrentView) {
        Q_ASSERT(m_CurrentView->prescriptionView());
        m_CurrentView->prescriptionView()->showDosageDialog();
    }
}
