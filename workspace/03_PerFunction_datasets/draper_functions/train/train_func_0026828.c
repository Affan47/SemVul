addEmoticonIndex(const QString &path, const QStringList &emoList)
{
    foreach(const QString &s, emoList) {
        KEmoticonsProvider::Emoticon e;
        QPixmap p;

        QString escaped = Qt::escape(s);
        e.picPath = path;
        p.load(path);

        e.picHTMLCode = QString("<img align=\"center\" title=\"%1\" alt=\"%1\" src=\"%2\" width=\"%3\" height=\"%4\" />").arg(escaped).arg(path).arg(p.width()).arg(p.height());

        e.matchTextEscaped = escaped;
        e.matchText = s;

        if (!s.isEmpty() && !escaped.isEmpty())
        {
            d->m_emoticonsIndex[escaped[0]].append(e);
            d->m_emoticonsIndex[s[0]].append(e);
        }
    }
}
