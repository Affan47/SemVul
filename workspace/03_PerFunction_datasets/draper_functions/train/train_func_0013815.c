operator+=(const plUnifiedTime& other) {
    fMicros += other.fMicros;
    if (fMicros > 1000000) {
        fSecs++;
        fMicros -= 1000000;
    }
    fSecs += other.fSecs;
    return *this;
}
