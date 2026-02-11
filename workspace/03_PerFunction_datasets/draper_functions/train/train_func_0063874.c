findMessage(const char *context, const char *sourceText,
                                          const char *comment,
                                          const QString &fileName, int lineNumber) const
{
    if (context == 0)
        context = "";
    if (sourceText == 0)
        sourceText = "";
    if (comment == 0)
        comment = "";

    QString myFilename = fileName;
    int myLineNumber = lineNumber;

    if (!d->messages.isEmpty()) {
        QMap<TranslatorMessage, void *>::const_iterator it;


        it = d->messages.find(TranslatorMessage(context, sourceText, comment, myFilename, myLineNumber));
        if (it != d->messages.constEnd())
            return it.key();

        if (comment[0]) {
            it = d->messages.find(TranslatorMessage(context, sourceText, "", myFilename, myLineNumber));
            if (it != d->messages.constEnd())
                return it.key();
        }
        it = d->messages.find(TranslatorMessage(context, "", comment, myFilename, myLineNumber));
        if (it != d->messages.constEnd())
            return it.key();
        if (comment[0]) {
            it = d->messages.find(TranslatorMessage(context, "", "", myFilename, myLineNumber));
            if (it != d->messages.constEnd())
                return it.key();
        }
        return TranslatorMessage();
    }

    return TranslatorMessage();
}
