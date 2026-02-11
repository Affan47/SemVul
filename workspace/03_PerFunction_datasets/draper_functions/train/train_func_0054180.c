checkStringValue(const OFString &value,
                                            const OFString &vm,
                                            const OFString &vr,
                                            const int vrID,
                                            const size_t maxLen,
                                            const OFString &charset)
{
    OFCondition result = EC_Normal;
    const size_t valLen = value.length();
    if (valLen > 0)
    {

        if (vm.empty())
        {

            if ((maxLen > 0) && (value.length() > maxLen))
                result = EC_MaximumLengthViolated;

            else if (charset.empty() || (charset == "ISO_IR 6") || (charset == "ISO_IR 100"))
            {

                if (DcmElement::scanValue(value, vr) != vrID)
                    result = EC_ValueRepresentationViolated;
            }
        } else {
            size_t posStart = 0;
            unsigned long vmNum = 0;

            while (posStart != OFString_npos)
            {
                ++vmNum;

                const size_t posEnd = value.find('\\', posStart);
                const size_t length = (posEnd == OFString_npos) ? valLen - posStart : posEnd - posStart;

                if ((maxLen > 0) && (length > maxLen))
                {
                    result = EC_MaximumLengthViolated;
                    break;
                }

                else if (charset.empty() || (charset == "ISO_IR 6") || (charset == "ISO_IR 100"))
                {

                    if (DcmElement::scanValue(value, vr, posStart, length) != vrID)
                    {
                        result = EC_ValueRepresentationViolated;
                        break;
                    }
                }
                posStart = (posEnd == OFString_npos) ? posEnd : posEnd + 1;
            }
            if (result.good())
            {

                result = DcmElement::checkVM(vmNum, vm);
            }
        }
    }
    return result;
}
