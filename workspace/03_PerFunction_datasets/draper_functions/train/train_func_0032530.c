commentsCount() const
{
    QString cstr = m_item.extractElementTextNS(slashNamespace(), QLatin1String("comments"));
    bool ok = false;
    int comments = cstr.toInt(&ok);
    return ok ? comments : -1;
}
