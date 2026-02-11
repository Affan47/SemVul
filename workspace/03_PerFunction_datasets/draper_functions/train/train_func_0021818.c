formCompletionItems(const QString &name) const
{
    if (!m_part->settings()->isFormCompletionEnabled())
        return QStringList();
    if (!d->formCompletions)
        d->formCompletions = new KConfig(KStandardDirs::locateLocal("data", "khtml/formcompletions"));
    return d->formCompletions->group("").readEntry(name, QStringList());
}
