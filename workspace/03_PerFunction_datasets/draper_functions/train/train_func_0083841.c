createGarminDeviceFromPath(string devicepath, TiXmlDocument *doc) {

    bool deleteXmlDoc = false;
    GpsDevice * device = NULL;

    if (doc == NULL) {
        DIR *dp;
        struct dirent *dirp;
        if((dp = opendir(devicepath.c_str())) == NULL) {
            Log::err("Error opening directory: "+devicepath);
            return NULL;
        }

        bool garminDirFound = false;
        string dirname = "";
        while ((dirp = readdir(dp)) != NULL) {
            dirname = string(dirp->d_name);
            if (GpsFunctions::iequals(dirname, "Garmin")) {
                garminDirFound = true;
                break;
            }
        }
        closedir(dp);

        if (garminDirFound) {
            string basePath = devicepath + "/" + dirname;
            string fullPath = basePath +"/GarminDevice.xml";


            if((dp = opendir(basePath.c_str())) != NULL) {
            	while ((dirp = readdir(dp)) != NULL) {
					string entry = string(dirp->d_name);
					if (GpsFunctions::iequals(entry, "GarminDevice.xml")) {
						fullPath = basePath + "/" + entry;
						break;
					}
				}
                closedir(dp);
            }

            doc = new TiXmlDocument(fullPath);
            deleteXmlDoc = true;
            if (!doc->LoadFile()) {
                deleteXmlDoc = false;
                delete(doc);
                doc = NULL;
                Log::info("Unable to load xml file "+fullPath);
            }
        } else {
            Log::dbg("Garmin directory not found at "+devicepath);
        }
    }

    if (doc != NULL) {
        TiXmlElement * node = doc->FirstChildElement("Device");
        if (node!=NULL) { node = node->FirstChildElement("Model"); }
        if (node!=NULL) { node = node->FirstChildElement("Description"); }
        if (node!=NULL) {

            string deviceName = node->GetText();

            GarminFilebasedDevice *fileDev = new GarminFilebasedDevice();
            fileDev->setBaseDirectory(devicepath);
            fileDev->setDeviceDescription(doc);
            fileDev->setDisplayName(deviceName);
            device = fileDev;

            Log::dbg("Found "+deviceName+" at "+devicepath);
        } else {
            Log::err("GarminDevice.xml has unexpected format!");
        }
    }

    if (deleteXmlDoc) {
        delete(doc);
        doc = NULL;
    }
    return device;
}
