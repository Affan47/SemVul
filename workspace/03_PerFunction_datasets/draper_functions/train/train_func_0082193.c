enumExtNames(UChar32 start, UChar32 end,
             UEnumCharNamesFn *fn, void *context)
{
    if(fn!=DO_FIND_NAME) {
        char buffer[200];
        uint16_t length;

        while(start<=end) {
            buffer[length = getExtName(start, buffer, sizeof(buffer))] = 0;

            if(length>0) {
                if(!fn(context, start, U_EXTENDED_CHAR_NAME, buffer, length)) {
                    return FALSE;
                }
            }
            ++start;
        }
    }

    return TRUE;
}
