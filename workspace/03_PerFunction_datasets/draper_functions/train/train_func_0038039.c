BitDepthFromString(const char * s)
    {
        std::string str = pystring::lower(s);
        if(str == "8ui") return BIT_DEPTH_UINT8;
        else if(str == "10ui") return BIT_DEPTH_UINT10;
        else if(str == "12ui") return BIT_DEPTH_UINT12;
        else if(str == "14ui") return BIT_DEPTH_UINT14;
        else if(str == "16ui") return BIT_DEPTH_UINT16;
        else if(str == "32ui") return BIT_DEPTH_UINT32;
        else if(str == "16f") return BIT_DEPTH_F16;
        else if(str == "32f") return BIT_DEPTH_F32;
        return BIT_DEPTH_UNKNOWN;
    }
