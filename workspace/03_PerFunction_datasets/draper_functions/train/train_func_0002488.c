saveDownloadData() {
    Log::dbg("saveDownloadData was called for "+this->displayName);
    if (downloadDataOutputStream.is_open()) {
        downloadDataOutputStream.close();
        if (!deviceDownloadList.empty()) {
            Log::dbg("Removing file to download from list");
        	DeviceDownloadData fileElement = deviceDownloadList.front();
        	deviceDownloadList.pop_front();
        	postProcessDownloadData(fileElement);
        }
    } else {
        Log::dbg("Not closing anything, since nothing was open...");
    }
}
