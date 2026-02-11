tagInfo(uint16_t tag, IfdId ifdId)
    {
        const TagInfo* ti = tagList(ifdId);
        if (ti == 0) return 0;
        int idx = 0;
        for (idx = 0; ti[idx].tag_ != 0xffff; ++idx) {
            if (ti[idx].tag_ == tag) break;
        }
        return &ti[idx];
    }
