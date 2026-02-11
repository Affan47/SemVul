run() {
        errors.clear();
        rideFile = new RideFile;
        rideFile->setDeviceType("o_synce macro/macrox");
        rideFile->setFileFormat("Macro GoldenCheetah Sync File (osyn)");

        if (!file.open(QIODevice::ReadOnly)) {
            delete rideFile;
            return NULL;
        }
        bool stop = false;

        int data_size = file.size();
        int bytes_read = 0;

        while (!stop && (bytes_read < data_size)) {
            bytes_read += read_page();
        }

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
