getTiXml(bool readTrackData, string fitnessDetailId) {
    TiXmlElement * xmlActivities = new TiXmlElement("Activities");


    sort (activityList.begin(), activityList.end(), activitySorter);

    vector<TcxActivity*>::iterator it;
    for ( it=activityList.begin() ; it < activityList.end(); ++it )
    {
        TcxActivity* activity = *it;
        if (!activity->isEmpty()) {
            if ((fitnessDetailId.length() == 0) || (fitnessDetailId.compare(activity->getId())==0)) {
                xmlActivities->LinkEndChild( activity->getTiXml(readTrackData) );
            }
        }
    }
    return xmlActivities;
}
