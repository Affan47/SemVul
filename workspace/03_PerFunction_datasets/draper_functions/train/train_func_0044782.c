prcWrite(pfPrcHelper* prc) {
    prc->startTag("plGenericType");
    prc->writeParam("Type", fType);

    switch (fType) {
    case kString:
    case kAny:
        prc->writeParam("Value", fString);
        break;
    case kBool:
        prc->writeParam("Value", fBool);
        break;
    case kByte:
        prc->writeParam("Value", fByte);
        break;
    case kInt:
        prc->writeParam("Value", fInt);
        break;
    case kUint:
        prc->writeParam("Value", fUint);
        break;
    case kFloat:
        prc->writeParam("Value", fFloat);
        break;
    case kDouble:
        prc->writeParam("Value", fDouble);
        break;
    }
    prc->endTag(true);
}
