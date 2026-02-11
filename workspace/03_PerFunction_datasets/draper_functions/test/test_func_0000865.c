StringToInt(int * ival, const char * str, bool failIfLeftoverChars)
    {
        if(!str) return false;
        if(!ival) return false;

        std::istringstream i(str);
        char c=0;
        if (!(i >> *ival) || (failIfLeftoverChars && i.get(c))) return false;
        return true;
    }
