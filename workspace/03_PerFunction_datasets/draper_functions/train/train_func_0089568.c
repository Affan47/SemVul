setLabel(const QString &label, const QString &lang)
{
    QString l = lang;
    if (lang.isEmpty()) {
        l = Trans::Constants::ALL_LANGUAGE;
    }
    d->m_Labels.insert(l, label);
}
