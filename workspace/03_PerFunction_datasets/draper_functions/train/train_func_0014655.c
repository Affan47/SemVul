removeIncompleteItems()
{
    Iterator = SeriesList.begin();
    const OFListIterator(SeriesStruct *) last = SeriesList.end();

    while (Iterator != last)
    {
        SeriesStruct *series = OFstatic_cast(SeriesStruct *, *Iterator);
        if (series != NULL)
        {

            if (series->InstanceList.empty())
            {

                delete series;

                Iterator = SeriesList.erase(Iterator);
            } else
                ++Iterator;
        } else
          ++Iterator;
    }
}
