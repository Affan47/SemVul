operator=(const TimeZoneTransition& right) {
    if (this != &right) {
        fTime = right.fTime;
        setFrom(*right.fFrom);
        setTo(*right.fTo);
    }
    return *this;
}
