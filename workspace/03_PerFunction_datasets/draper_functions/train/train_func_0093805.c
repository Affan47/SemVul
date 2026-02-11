writeXML(STD_NAMESPACE ostream &stream,
                                                  const size_t flags) const
{
    OFCondition result = EC_Normal;

    OFListConstIterator(StudyStruct *) iter = StudyList.begin();
    const OFListConstIterator(StudyStruct *) last = StudyList.end();
    while ((iter != last) && result.good())
    {
        StudyStruct *study = OFstatic_cast(StudyStruct *, *iter);

        if (study != NULL)
        {

            result = study->writeXML(stream, flags);
        }
        iter++;
    }
    return result;
}
