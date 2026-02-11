printProperties(std::ostream& os, const std::string& prefix)
    {
        const XmpPropertyInfo* pl = propertyList(prefix);
        if (pl) {
            for (int i = 0; pl[i].name_ != 0; ++i) {
                os << pl[i];
            }
        }

    }
