getStatusBarInfo() const
{
    if (!d)
        return QString();

    QString text = d->m_strText;
    const QString comment = mimeComment();

    if ( d->m_bLink )
    {
        text += ' ';
        if ( comment.isEmpty() )
            text += i18n ( "(Symbolic Link to %1)", linkDest() );
        else
            text += i18n("(%1, Link to %2)", comment, linkDest());
    }
    else if ( targetUrl() != url() )
    {
        text += i18n ( " (Points to %1)", targetUrl().pathOrUrl());
    }
    else if ( S_ISREG( d->m_fileMode ) )
    {
        text += QString(" (%1, %2)").arg( comment, KIO::convertSize( size() ) );
    }
    else
    {
        text += QString(" (%1)").arg( comment );
    }
    return text;
}
