run() {
        errors.clear();
        rideFile = new RideFile;
        rideFile->setDeviceType("Joule GPS");
        rideFile->setFileFormat("CycleOps Joule (bin2)");
        rideFile->setRecIntSecs(1);

        if (!file.open(QIODevice::ReadOnly)) {
            delete rideFile;
            return NULL;
        }
        bool stop = false;

        int data_size = file.size();
        int bytes_read = 0;

        bytes_read += read_version();
        bytes_read += read_system_info();
        bytes_read += read_summary_page();

        while (!stop && (bytes_read < data_size)) {
            bytes_read += read_detail_page();
        }

        rideFile->setTag("Device Info", deviceInfo);

        if (stop) {
            file.close();
            delete rideFile;
            return NULL;

        } else {
            file.close();
            return rideFile;
        }
    }
}
