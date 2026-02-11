startReadFitnessData(string dataTypeName) {
    if (Log::enabledDbg()) Log::dbg("Starting thread to read from garmin device ("+dataTypeName+")");

    if (dataTypeName.compare("FitnessUserProfile")==0) {
        this->workType = READFITNESSUSERPROFILE;
    } else if (dataTypeName.compare("FitnessWorkouts")==0) {
        this->workType = READFITNESSWORKOUTS;
    } else if (dataTypeName.compare("FitnessCourses")==0) {
        this->workType = READFITNESSCOURSES;
    } else if (dataTypeName.compare("FitnessHistory")==0) {
        this->workType = READFITNESS;
    } else {
        Log::err("Unknown data to read: '"+dataTypeName+"' - Defaulting back to FitnessHistory");
        this->workType = READFITNESS;
    }

    if (startThread()) {
        return 1;
    }

    return 0;
}
