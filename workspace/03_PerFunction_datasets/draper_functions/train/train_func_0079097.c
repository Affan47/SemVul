checkPathsFromConfiguration() {
    for (list<MassStorageDirectoryType>::iterator it = deviceDirectories.begin(); it != deviceDirectories.end(); ++it) {
        MassStorageDirectoryType const& currentDir = (*it);
        string fullDirectoryName = this->baseDirectory + "/" + currentDir.path;
        struct stat st;

        if(stat(fullDirectoryName.c_str(),&st) != 0) {

            if (Log::enabledInfo()) { Log::info("Directory "+currentDir.path+" does not exist on device, searching alternative upper/lowercase writings");}
            bool foundNewPath = true;
            stringstream ss(currentDir.path);
            string existingSubPath = "";
            string item;
            while(std::getline(ss, item, '/')) {
                string parentPath = this->baseDirectory;
                if (existingSubPath.length() > 0) {
                    parentPath += "/" + existingSubPath;
                }
                string pathToTest = parentPath + "/" + item;


                if(stat(pathToTest.c_str(),&st) != 0) {


                    DIR *dp;
                    struct dirent *dirp;
                    if((dp = opendir(parentPath.c_str())) != NULL) {
                        bool foundEntry = false;
                        while ((dirp = readdir(dp)) != NULL) {
                            string fileName = string(dirp->d_name);

                            if ((fileName.length() == item.length()) &&
                               (strncasecmp(fileName.c_str(), item.c_str(), item.length()) == 0)) {
                                item = fileName;
                                foundEntry = true;
                                break;
                            }
                        }
                        closedir(dp);
                        if (!foundEntry) { foundNewPath = false; }
                    } else {
                        if (Log::enabledDbg()) { Log::dbg("Unable to open directory "+parentPath+" while searching for "+currentDir.path); }
                    }

                }
                if (existingSubPath.length() > 0) { existingSubPath += "/"; }
                existingSubPath += item;
            }

            if (foundNewPath) {
                if (currentDir.path.length() > 0) {
                    std::string::const_iterator it = currentDir.path.end() - 1;
                    if (*it == '/') {
                        existingSubPath += "/";
                    }
                }
                Log::info("Overwriting "+ currentDir.path + " from configuration with " + existingSubPath);
            } else {
                if (Log::enabledDbg()) { Log::dbg("No alternative found for "+currentDir.path);}
            }
        }
    }
}
