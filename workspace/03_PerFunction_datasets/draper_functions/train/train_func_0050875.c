removeIncompleteItems()
{
    Iterator = StudyList.begin();
    const OFListIterator(StudyStruct *) last = StudyList.end();

    while (Iterator != last)
    {
        StudyStruct *study = OFstatic_cast(StudyStruct *, *Iterator);
        if (study != NULL)
        {

            study->removeIncompleteItems();

            if (study->SeriesList.empty())
            {

                delete study;

                Iterator = StudyList.erase(Iterator);
            } else
                ++Iterator;
        } else
          ++Iterator;
    }
}
