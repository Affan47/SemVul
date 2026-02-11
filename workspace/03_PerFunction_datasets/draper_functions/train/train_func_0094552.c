addRecord(const UnicodeString &name, const void *data, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return *this;
    }
    Record *r = new Record(this, name, data);
    inputRecords_->addElement(r, status);
    indexBuildRequired_ = TRUE;


    return *this;
}
