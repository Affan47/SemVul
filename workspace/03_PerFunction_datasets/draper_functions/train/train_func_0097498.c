checkValue(const OFString &vm,
                                         const OFBool )
{
    OFString strVal;

    OFCondition l_error = getStringValue(strVal);
    if (l_error.good())
        l_error = DcmIntegerString::checkStringValue(strVal, vm);
    return l_error;
}
