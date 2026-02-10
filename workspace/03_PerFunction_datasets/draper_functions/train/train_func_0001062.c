gotoInstance(const OFString &instanceUID)
{
    InstanceStruct *instance = NULL;

    Iterator = SeriesList.begin();
    const OFListIterator(SeriesStruct *) last = SeriesList.end();

    while ((Iterator != last) && (instance == NULL))
    {
        SeriesStruct *series = OFstatic_cast(SeriesStruct *, *Iterator);

        if (series != NULL)
            instance = series->gotoInstance(instanceUID);

        if (instance == NULL)
            Iterator++;
    }
    return instance;
}
