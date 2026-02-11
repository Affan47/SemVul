getTiXml() {
    TiXmlElement * xmlTrack = new TiXmlElement("Track");
    vector<TcxTrackpoint*>::iterator it;
    for ( it=trackpointList.begin() ; it < trackpointList.end(); ++it )
    {
        TcxTrackpoint* trackpoint = *it;
        xmlTrack->LinkEndChild(trackpoint->getTiXml());
    }
    return xmlTrack;
}
