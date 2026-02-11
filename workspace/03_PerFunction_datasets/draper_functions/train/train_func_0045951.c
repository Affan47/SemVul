count(UErrorCode& status) const {
        return upToDate(status) ? _ids.size() : 0;
    }
