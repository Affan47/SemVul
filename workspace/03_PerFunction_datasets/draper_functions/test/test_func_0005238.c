getRecordName() const {
    const UnicodeString *retStr = &emptyString_;
    if (currentBucket_ != NULL && currentBucket_->records_ != NULL &&
        itemsIterIndex_ >= 0 &&
        itemsIterIndex_ < currentBucket_->records_->size()) {
            Record *item = static_cast<Record *>(currentBucket_->records_->elementAt(itemsIterIndex_));
            retStr = &item->name_;
    }
    return *retStr;
}
