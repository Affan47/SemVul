replaceTokens(QString &textToAnalyse, const QHash<QString, QString> &tokens_values)
{
    if (tokens_values.isEmpty())
        return 0;
    int i = 0;
    foreach(const QString &tok, tokens_values.keys()) {
        i += replaceToken(textToAnalyse, tok, tokens_values.value(tok));
    }
    return i;
}
