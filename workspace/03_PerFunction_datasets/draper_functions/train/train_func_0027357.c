slotUpdateConfigureExcludedLabelsLabel()
{
    QLabel *label = findChild<QLabel *>( "configureLabelExceptions" );
    if( !label || !m_statSyncingConfig )
    {
        warning() << __PRETTY_FUNCTION__ << "label or m_statSyncingConfig is null!";
        return;
    }
    int exceptions = m_statSyncingConfig.data()->excludedLabels().count();
    QString begin = "<a href='dummy'>";
    QString end = "</a>";
    label->setText( i18np( "(%2one exception%3)", "(%2%1 exceptions%3)", exceptions,
                           begin, end ) );
}
