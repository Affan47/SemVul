setDefaultFont(const QFont &font)
{
    document()->setDefaultFont(font);
    if (font.pointSize() > 0)
        setFontPointSize(font.pointSize());
    else
        setFontPointSize(QFontInfo(font).pointSize());
    emit textChanged();
}
