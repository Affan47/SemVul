write(DcmItem &dataset) const
{
    OFCondition result = EC_Normal;

    OFListConstIterator(StudyStruct *) iter = StudyList.begin();
    const OFListConstIterator(StudyStruct *) last = StudyList.end();
    while ((iter != last) && result.good())
    {
        StudyStruct *study = OFstatic_cast(StudyStruct *, *iter);

        if (study != NULL)
        {
            DcmItem *item = NULL;

            result = dataset.findOrCreateSequenceItem(SequenceTag, item, -2 );

            if (result.good())
                result = study->write(*item);
        }
        iter++;
    }
    return result;
}
