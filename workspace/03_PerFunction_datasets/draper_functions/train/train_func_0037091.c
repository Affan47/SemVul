data(const int ref, const int role) const
{
    if (role==Qt::DisplayRole || role==Form::IFormItemData::PatientModelRole) {
        switch (ref) {
        case ID_EpisodeDate: return m_Form->m_EpisodeDate->dateTime();
        case ID_EpisodeLabel: return m_Form->m_EpisodeLabel->text();
        case ID_UserName: return m_Data.value(ID_UserName);
        case ID_Priority: return m_Form->currentPriority();
        }
    }
    return QVariant();
}
