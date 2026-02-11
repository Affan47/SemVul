toString(LogLevel ll) const
{
    ToStringNode* toStringTmp = GET_TO_STRING_NODE;
    while(toStringTmp) {
        tstring ret = toStringTmp->method(ll);
        if(ret.length() > 0) {
            return ret;
        }
        toStringTmp = toStringTmp->next;
    }

    return _UNKNOWN_STRING;
}
