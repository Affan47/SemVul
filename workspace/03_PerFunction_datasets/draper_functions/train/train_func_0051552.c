NCMessageSize(const msgparm_t* data, const pnNetMsg* msg)
{
    size_t bufSize = 0;
    unsigned int size = 0;
    unsigned int count = 0;

    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            if (field->fCount == 0)
                bufSize += field->fSize;
            else
                bufSize += field->fSize * field->fCount;
            break;
        case kFieldString:
            bufSize += sizeof(uint16_t);
            bufSize += plwcslen(data[i].fString) * sizeof(pl_wchar_t);
            break;
        case kFieldVarCount:
            bufSize += sizeof(uint32_t);
            count = data[i].fUint;
            size = field->fSize;
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            bufSize += count * size;
            count = 0;
            size = 0;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            bufSize += field->fCount * field->fSize;
            break;
        }
    }
    return bufSize;
}
