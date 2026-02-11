isValid(const QStringList &listOfStrings, QPair<int, int> *where,
             const QString &alphabet)
{
    CharSet seen;
    for (int i = 0; i < listOfStrings.count(); ++i) {
        QString string = listOfStrings.at(i);
        string = string.replace("&&", "");
        int j = string.indexOf("&");
        if (j > -1 && j + 1 < string.length()) {
            const QChar c = string.at(j + 1).toUpper();
            if (seen.contains(c) || !alphabet.contains(c)) {
                if (where) {
                    where->first = i;
                    where->second = j;
                }
                return false;
            }
            seen.insert(c);
        }
    }
    return true;
}
