LastByte() {
        if (buffer_ != NULL && appended_ > 0) {
            return reinterpret_cast<uint8_t *>(buffer_)[appended_ - 1];
        } else {
            return lastResortByte_;
        }
    }
