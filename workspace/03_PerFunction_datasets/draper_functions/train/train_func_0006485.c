makeCompletion(const QString& string)
{
    if (string.isEmpty()) {
        d->itemView->selectionModel()->clear();
        return QString();
    }

    prepareCompletionObjects();
    return d->completion.makeCompletion(string);
}
