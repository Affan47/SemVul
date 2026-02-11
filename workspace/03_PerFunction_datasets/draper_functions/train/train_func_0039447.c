getTiXml(bool readTrackData) {
    TiXmlElement * xmlActivity = new TiXmlElement("Activity");

    switch (this->sportType) {
        case TrainingCenterDatabase::Running:
            xmlActivity->SetAttribute("Sport","Running");
            break;
        case TrainingCenterDatabase::Biking:
            xmlActivity->SetAttribute("Sport","Biking");
            break;
        default:
            xmlActivity->SetAttribute("Sport","Other");
            break;
    }

    TiXmlElement * xmlId = new TiXmlElement("Id");
    xmlActivity->LinkEndChild(xmlId);
    xmlId->LinkEndChild(new TiXmlText(this->id));

    vector<TcxLap*>::iterator it;
    for ( it=lapList.begin() ; it < lapList.end(); ++it )
    {
        TcxLap* lap = *it;
        xmlActivity->LinkEndChild( lap->getTiXml(readTrackData) );
    }

    if (this->creator != NULL) {
        xmlActivity->LinkEndChild(this->creator->getTiXml());
    }
    return xmlActivity;
}
