getItemTitleFormatInfo(bool* containsMarkup) const
{
    if (!d->itemTitlesGuessed)
    {
        QString titles;
        QList<Item> litems = items();

        if (litems.isEmpty())
        {
            d->itemTitlesGuessed = true;
            return;
        }

        int nmax = litems.size() < 10 ? litems.size() : 10;
        int i = 0;

        QList<Item>::ConstIterator it = litems.constBegin();

        while (i < nmax)
        {
            titles += (*it).originalTitle();
            ++it;
            ++i;
        }

        d->itemTitleContainsMarkup = stringContainsMarkup(titles);
        d->itemTitlesGuessed = true;
    }
    if (containsMarkup != 0L)
        *containsMarkup = d->itemTitleContainsMarkup;
}
