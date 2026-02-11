shouldStartCompletion(View* view, const QString &insertedText, bool userInsertion, const Cursor &position)
{
    Q_UNUSED(view);
    Q_UNUSED(position);
    if(insertedText.isEmpty())
        return false;

    QChar lastChar = insertedText.at(insertedText.count() - 1);
    if ((userInsertion && (lastChar.isLetter() || lastChar.isNumber() || lastChar == '_')) ||
        lastChar == '.' || insertedText.endsWith(QLatin1String("->"))) {
        return true;
    }
    return false;
}
