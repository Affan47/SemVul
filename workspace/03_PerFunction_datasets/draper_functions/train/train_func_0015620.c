defaultCount(const ExifKey& key)
    {
        const TagInfo* ti = tagInfo(key.tag(), static_cast<Internal::IfdId>(key.ifdId()));
        if (ti == 0) return unknownTag.count_;
        return ti->count_;
    }
