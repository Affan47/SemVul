test(const int typeOfInteraction, const int typeOfSubstrat, const QString &drugUid, const QStringList &toTest)
{
    if (typeOfSubstrat!=Drug && toTest.isEmpty()) {
        return false;
    }

    for(int i = 0; i < m_Cache.count(); ++i) {

        const DrugAllergyEngineCache &c = m_Cache.at(i);
        if (c.typeOfInteraction!=typeOfInteraction)
            continue;


        const QStringList &l = c.bySubstrat.values(typeOfSubstrat);
        if (l.isEmpty())
            continue;


        if (typeOfSubstrat==ClassInn) {
            foreach(const QString &test, toTest) {

                foreach(const QString &s, l) {
                    if (test.startsWith(s, Qt::CaseInsensitive)) {
                        m_ComputedInteractionCache.insertMulti(drugUid, typeOfInteraction);
                        return true;
                    }
                }
            }
        } else if (typeOfSubstrat==InnCode) {
            foreach(const QString &test, toTest) {

                if (l.contains(test, Qt::CaseInsensitive)) {
                    m_ComputedInteractionCache.insertMulti(drugUid, typeOfInteraction);
                    return true;
                }
            }
        } else if (typeOfSubstrat==Drug) {
            if (l.contains(drugUid, Qt::CaseInsensitive)) {
                m_ComputedInteractionCache.insertMulti(drugUid, typeOfInteraction);
                return true;
            }
        }
    }
    return false;
}
