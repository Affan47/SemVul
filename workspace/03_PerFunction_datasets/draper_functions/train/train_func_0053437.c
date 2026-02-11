u_wmsg_errorName(UErrorCode err)
{
    UChar *msg;
    int32_t msgLen;
    UErrorCode subErr = U_ZERO_ERROR;
    const char *textMsg = NULL;


    msg = (UChar*)fetchErrorName(err);

    if(msg)
    {
        return msg;
    }

    if(gBundle == NULL)
    {
        msg = NULL;
    }
    else
    {
        const char *errname = u_errorName(err);
        if (errname) {
            msg = (UChar*)ures_getStringByKey(gBundle, errname, &msgLen, &subErr);
            if(U_FAILURE(subErr))
            {
                msg = NULL;
            }
        }
    }

    if(msg == NULL)
    {
        char error[128];
        textMsg = u_errorName(err);
        if (!textMsg) {
            sprintf(error, "UNDOCUMENTED ICU ERROR %d", err);
            textMsg = error;
        }
        msg = (UChar*)malloc((strlen(textMsg)+1)*sizeof(msg[0]));
        u_charsToUChars(textMsg, msg, (int32_t)(strlen(textMsg)+1));
    }

    if(err>=0)
        gErrMessages[err] = msg;
    else
        gInfoMessages[err-U_ERROR_WARNING_START] = msg;

    return msg;
}
