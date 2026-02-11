aboutToRemoveObject(QObject *obj)
{
    IMode *mode = Aggregation::query<IMode>(obj);
    if (!mode)
        return;

    const int index = d->m_modes.indexOf(mode);
    d->m_modes.remove(index);
    d->m_modeShortcuts.remove(index);
    d->m_modeStack->removeTab(index);

    contextManager()->removeContextObject(mode);
}
