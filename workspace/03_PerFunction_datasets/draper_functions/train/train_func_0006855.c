startFindDevices() {
	this->findDeviceState=1;
	int code = pthread_create(&(this->threadId), NULL, DeviceManager::findDeviceThread, (void*)this);

    if (code != 0) {
        Log::err("Creation of findDevices thread failed!");
        this->findDeviceState=0;
        return;
    }
}
