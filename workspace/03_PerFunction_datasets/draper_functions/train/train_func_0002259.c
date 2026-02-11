checkElementValue(DcmElement &delem,
                                   const OFString &vm,
                                   const OFString &type,
                                   const OFCondition &searchCond,
                                   const char *moduleName)
{
    OFBool result = OFTrue;
    DcmTag tag = delem.getTag();
    const OFString tagName = tag.getTagName();
    const OFString module = (moduleName == NULL) ? "SR document" : moduleName;
    unsigned long vmNum;
    OFString vmText;

    if (delem.getVR() == EVR_SQ)
    {
        vmNum = OFstatic_cast(DcmSequenceOfItems &, delem).card();
        vmText = " #items";
    } else {
        vmNum = delem.getVM();
        vmText = " VM";
    }

    if (((type == "1") || (type == "2")) && searchCond.bad())
    {
        DCMSR_WARN(tagName << " " << tag << " absent in " << module << " (type " << type << ")");
        result = OFFalse;
    }
    else if (delem.isEmpty(OFTrue ))
    {

        if (((type == "1") || (type == "1C")) && searchCond.good())
        {
            DCMSR_WARN(tagName << " " << tag << " empty in " << module << " (type " << type << ")");
            result = OFFalse;
        }
    } else {
        const OFCondition checkResult = delem.checkValue(vm, OFTrue );
        if (checkResult == EC_ValueRepresentationViolated)
        {
            DCMSR_WARN(tagName << " " << tag << " violates VR definition in " << module);
            result = OFFalse;
        }
        else if (checkResult == EC_ValueMultiplicityViolated)
        {
            DCMSR_WARN(tagName << " " << tag << vmText << " != " << vm << " in " << module);
            result = OFFalse;
        }
        else if (checkResult == EC_MaximumLengthViolated)
        {
            DCMSR_WARN(tagName << " " << tag << " violates maximum VR length in " << module);
            result = OFFalse;
        }
        else if (checkResult.bad())
        {
            DCMSR_DEBUG("INTERNAL ERROR while checking value of " << tagName << " " << tag << " in " << module);
        }
    }
    return result;
}
