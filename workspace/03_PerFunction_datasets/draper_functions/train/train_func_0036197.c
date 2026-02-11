isDeviceAvailable() {
    struct stat st;
    if(stat(this->baseDirectory.c_str(),&st) == 0) {

        return true;
    }
    Log::dbg("Device is not available: "+this->displayName);
    return false;
}
