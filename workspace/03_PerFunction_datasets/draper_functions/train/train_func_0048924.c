decodeIptc(const TiffEntryBase* object)
    {

        decodeStdTiffEntry(object);


        if (decodedIptc_) {
            return;
        }
        decodedIptc_ = true;

        byte const* pData = 0;
        long size = 0;
        getObjData(pData, size, 0x83bb, ifd0Id, object);
        if (pData) {
            if (0 == IptcParser::decode(iptcData_, pData, size)) {
                return;
            }
#ifndef SUPPRESS_WARNINGS
            else {
                EXV_WARNING << "Failed to decode IPTC block found in "
                            << "Directory Image, entry 0x83bb\n";
            }
#endif
        }


        pData = 0;
        size = 0;
        getObjData(pData, size, 0x8649, ifd0Id, object);
        if (pData) {
            byte const* record = 0;
            uint32_t sizeHdr = 0;
            uint32_t sizeData = 0;
            if (0 != Photoshop::locateIptcIrb(pData, size,
                                              &record, &sizeHdr, &sizeData)) {
                return;
            }
            if (0 == IptcParser::decode(iptcData_, record + sizeHdr, sizeData)) {
                return;
            }
#ifndef SUPPRESS_WARNINGS
            else {
                EXV_WARNING << "Failed to decode IPTC block found in "
                            << "Directory Image, entry 0x8649\n";
            }
#endif
        }
    }
