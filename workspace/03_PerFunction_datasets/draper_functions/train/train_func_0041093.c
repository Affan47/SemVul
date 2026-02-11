escape (const QString &text)
{
    int tlen = text.length();
    QString ntext;
    ntext.reserve(tlen);
    for (int i = 0; i < tlen; ++i) {
        QChar c = text[i];
        if (c == QLatin1Char('&')) {
            ntext += QLatin1String("&amp;");
        } else if (c == QLatin1Char('<')) {
            ntext += QLatin1String("&lt;");
        } else if (c == QLatin1Char('>')) {
            ntext += QLatin1String("&gt;");
        } else if (c == QLatin1Char('\'')) {
            ntext += QLatin1String("&apos;");
        } else if (c == QLatin1Char('"')) {
            ntext += QLatin1String("&quot;");
        } else {
            ntext += c;
        }
    }

    return ntext;
}
