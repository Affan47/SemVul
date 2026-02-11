checkStringValue(const OFString &value,
                                      const OFString &vm,
                                      const OFBool oldFormat)
{
    OFCondition result = EC_Normal;
    const size_t valLen = value.length();
    if (valLen > 0)
    {
        size_t posStart = 0;
        unsigned long vmNum = 0;

        while (posStart != OFString_npos)
        {
            ++vmNum;

            const size_t posEnd = value.find('\\', posStart);
            const size_t length = (posEnd == OFString_npos) ? valLen - posStart : posEnd - posStart;
            if (dcmEnableVRCheckerForStringValues.get())
            {

                const int vrID = DcmElement::scanValue(value, "da", posStart, length);
                if ((vrID != 2) && (!oldFormat || (vrID != 3)) && (vrID != 17))
                {
                    result = EC_ValueRepresentationViolated;
                    break;
                }
            }
            posStart = (posEnd == OFString_npos) ? posEnd : posEnd + 1;
        }
        if (result.good() && !vm.empty())
        {

            result = DcmElement::checkVM(vmNum, vm);
        }
    }
    return result;
}
