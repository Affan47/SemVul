historyAdd(const QChar &c, bool fromSearch, const QString &searchString)
{


    if (!historyEnabled) {
        return;
    }

    if (!history.isEmpty() && c == history.last().c) {

        return;
    }


    while (!history.isEmpty() && inHistory != history.count() - 1) {
        history.removeLast();
    }

    while (history.size() >= MaxHistoryItems) {
        history.removeFirst();
    }

    HistoryItem item;
    item.c = c;
    item.fromSearch = fromSearch;
    item.searchString = searchString;
    history.append(item);

    inHistory = history.count() - 1;
    updateBackForwardButtons();
}
