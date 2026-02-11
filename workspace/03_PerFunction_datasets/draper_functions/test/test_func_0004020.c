_k_setTextBackgroundColor()
{
    QTextCharFormat fmt = q->textCursor().charFormat();
    QColor currentTextBackgroundColor = fmt.background().color();

    const int result = KColorDialog::getColor(currentTextBackgroundColor, KColorScheme(QPalette::Active, KColorScheme::View).foreground().color() , q);
    if (result != QDialog::Accepted)
        return;
    if (!currentTextBackgroundColor.isValid())
        currentTextBackgroundColor = KColorScheme(QPalette::Active, KColorScheme::View).foreground().color() ;

    q->setTextBackgroundColor(currentTextBackgroundColor);

}
