addFilter(const QString& filterStr)
{
    QString filter = filterStr;


    QChar firstChar = filter.at(0);
    if (firstChar == QLatin1Char('[') || firstChar == QLatin1Char('!') || firstChar == QLatin1Char('&') || firstChar == QLatin1Char('#') || filter.contains(QLatin1Char('#')))
        return;


    int first = 0;
    int last  = filter.length() - 1;
    if (filter.startsWith(QLatin1String("@@")))
        first = 2;


    int dollar = filter.lastIndexOf(QLatin1Char('$'));
    if (dollar != -1) {
        last = dollar - 1;

        if (first == last && firstChar == QLatin1Char('*'))
            return;
    }


    if (first > last)
        return;

    filter = filter.mid(first, last - first + 1);


    if (filter.length()>2 && filter.startsWith(QLatin1Char('/')) && filter.endsWith(QLatin1Char('/')))
    {
        QString inside = filter.mid(1, filter.length()-2);
        QRegExp rx(inside);
        reFilters.append(rx);

    }
    else
    {


        first = 0;
        last  = filter.length() - 1;

        while (first < filter.length() && filter[first] == QLatin1Char('*'))
            ++first;

        while (last >= 0 && filter[last] == QLatin1Char('*'))
            --last;

        if (first > last)
            filter = QLatin1String("*");
        else
            filter = filter.mid(first, last - first + 1);


        if (filter.contains("*"))
        {

            int aPos = filter.indexOf('*');
            if (aPos < 0)
                aPos = filter.length();
            if (aPos > 7) {
                QRegExp rx = fromAdBlockWildcard(filter.mid(aPos) + QLatin1Char('*'));

                stringFiltersMatcher.addWildedString(filter.mid(0, aPos), rx);
            } else {
                QRegExp rx = fromAdBlockWildcard(filter);
                reFilters.append(rx);
            }
        }
        else
        {

            stringFiltersMatcher.addString(filter);
        }
    }
}
