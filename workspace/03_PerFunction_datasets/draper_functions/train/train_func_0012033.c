taglist(std::ostream& os, IfdId ifdId)
    {
        const TagInfo* ti = Internal::tagList(ifdId);
        if (ti != 0) {
            for (int k = 0; ti[k].tag_ != 0xffff; ++k) {
                os << ti[k] << "\n";
            }
        }
    }
