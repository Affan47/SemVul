fontSmaller()
{
    QFont font = textEdit()->textCursor().charFormat().font();
    QTextCharFormat fmt;
    font.setPointSize(font.pointSize() - 1);
    fmt.setFont(font);
    d->mergeFormatOnWordOrSelection(fmt);
}
