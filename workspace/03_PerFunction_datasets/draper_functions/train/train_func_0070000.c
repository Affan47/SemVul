GetTag(const std::string& tag, float& destination) const {


    if ( SupportData.HasCoreOnly || TagData.empty() )
        return false;


    char* pTagData = (char*)TagData.data();
    const unsigned int tagDataLength = TagData.size();
    unsigned int numBytesParsed = 0;


    if ( Internal::FindTag(tag, pTagData, tagDataLength, numBytesParsed) ) {


        const char type = *(pTagData - 1);
        int destinationLength = 0;
        switch (type) {


            case (Constants::BAM_TAG_TYPE_ASCII) :
            case (Constants::BAM_TAG_TYPE_INT8)  :
            case (Constants::BAM_TAG_TYPE_UINT8) :
                destinationLength = 1;
                break;


            case (Constants::BAM_TAG_TYPE_INT16)  :
            case (Constants::BAM_TAG_TYPE_UINT16) :
                destinationLength = 2;
                break;


            case (Constants::BAM_TAG_TYPE_FLOAT)  :
            case (Constants::BAM_TAG_TYPE_INT32)  :
            case (Constants::BAM_TAG_TYPE_UINT32) :
                destinationLength = 4;
                break;


            case (Constants::BAM_TAG_TYPE_STRING) :
            case (Constants::BAM_TAG_TYPE_HEX)    :
                fprintf(stderr, "BamAlignment ERROR: cannot store tag of type %c in float destination\n", type);
                return false;


            default:
                fprintf(stderr, "BamAlignment ERROR: unknown tag type encountered: [%c]\n", type);
                return false;
        }


        destination = 0.0;
        memcpy(&destination, pTagData, destinationLength);
        return true;
    }


    return false;
}
