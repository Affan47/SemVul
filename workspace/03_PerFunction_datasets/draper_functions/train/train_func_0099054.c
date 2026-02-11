tagNumber(const std::string& tagName, IfdId ifdId)
    {
        const TagInfo* ti = tagInfo(tagName, ifdId);
        if (ti != 0 && ti->tag_ != 0xffff) return ti->tag_;
        if (!isHex(tagName, 4, "0x")) throw Error(7, tagName, ifdId);
        std::istringstream is(tagName);
        uint16_t tag;
        is >> std::hex >> tag;
        return tag;
    }
