getDevicesXML()
{

    TiXmlDocument doc;
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "no" );
	TiXmlElement * devices = new TiXmlElement( "Devices" );
    devices->SetAttribute("xmlns", "http://www.garmin.com/xmlschemas/PluginAPI/v1");

    int deviceCount = 0;

    vector<GpsDevice*>::iterator it=gpsDeviceList.begin();
    while(it != gpsDeviceList.end()){

        if( !(*it)->isDeviceAvailable() ){
            delete *it;
            it = gpsDeviceList.erase(it);
            continue;
        } else {
            TiXmlElement *device = new TiXmlElement ( "Device" );
            device->SetAttribute("DisplayName", (*it)->getDisplayName());
            device->SetAttribute("Number", deviceCount);
            devices->LinkEndChild( device );
            deviceCount++;
        }
        ++it;
    }

    if (Log::enabledDbg()) {
        std::ostringstream dbgOut;
        dbgOut << "getDeviceXML returns " << deviceCount << " devices";
        Log::dbg(dbgOut.str());
    }

    doc.LinkEndChild( decl );
    doc.LinkEndChild( devices );

    TiXmlPrinter printer;
	printer.SetIndent( "\t" );
	doc.Accept( &printer );
    string str = printer.Str();

    return str;
}
