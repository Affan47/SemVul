formatFromTags (const QString &text)
{
    KuitSemanticsStaticData *s = semanticsStaticData;
    static QRegExp staticTagRx(QString::fromLatin1("<\\s*(\\w+)[^>]*>"));

    QRegExp tagRx = staticTagRx;
    int p = tagRx.indexIn(text);
    while (p >= 0) {
        QString tagname = tagRx.capturedTexts().at(1).toLower();
        if (s->qtHtmlTagNames.contains(tagname)) {
            return Kuit::Fmt::Rich;
        }
        p = tagRx.indexIn(text, p + tagRx.matchedLength());
    }
    return Kuit::Fmt::Plain;
}
