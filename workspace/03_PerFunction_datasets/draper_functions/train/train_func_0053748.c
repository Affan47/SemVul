parentApp() const {
    Q_D(const KService);
    QMap<QString,QVariant>::ConstIterator it = d->m_mapProps.find(QLatin1String("X-KDE-ParentApp"));
    if ( (it == d->m_mapProps.end()) || (!it->isValid()))
    {
        return QString();
    }

    return it->toString();
}
