exceptionRule() const
{
    QSet<QOrganizerRecurrenceRule> exrules = exceptionRules();
    if (!exrules.isEmpty())
        return *exrules.begin();
    return QOrganizerRecurrenceRule();
}
