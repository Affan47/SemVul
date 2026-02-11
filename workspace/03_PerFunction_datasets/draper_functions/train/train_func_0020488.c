hasBeenIgated(void)
{
    int i;
    bool rv = false;

    if (valid_ax25 == false)
        return false;

    if (aprsType == APRS3RDPARTY){
        i = thirdPartyPathSize - 1;
        while ((i > 0) && (rv == false)){
            rv = igated(thirdPartyPath[i--]);
        }
    }
    return rv;
}
