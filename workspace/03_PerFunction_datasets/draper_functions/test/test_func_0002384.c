doWork() {

    if ((this->workType == WRITEGPX) ||
        (this->workType == WRITEFITNESSDATA)) {
        this->writeGpxFile();
    } else if (this->workType == READFITNESS) {
        this->readFitnessDataFromDevice(true, "");
    } else if (this->workType == READFITNESSDIR) {
        this->readFitnessDataFromDevice(false, "");
    } else if (this->workType == READFITNESSDETAIL) {
        this->readFitnessDataFromDevice(true, this->readFitnessDetailId);
    } else if (this->workType == READFITDIRECTORY) {
        this->readFITDirectoryFromDevice();
    } else if (this->workType == READABLEFILELISTING) {
        this->readFileListingFromDevice();
    } else if (this->workType == READFITNESSUSERPROFILE) {
        this->readFitnessUserProfile();
    } else if (this->workType == READFITNESSCOURSES) {
        this->readFitnessCourses(true);
    } else if (this->workType == READFITNESSCOURSESDIR) {
        this->readFitnessCourses(false);
    } else if (this->workType == READFITNESSWORKOUTS) {
        this->readFitnessWorkouts();
    } else if (this->workType == DIRECTORYLISTING) {
        this->readDirectoryListing();
    } else {
        Log::err("Work Type not implemented!");
    }
}
