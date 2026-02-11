ajUtilGetBigendian(void)
{
    static union lbytes
    {
        char chars[sizeof(ajint)];
        ajint i;
    } data;

    if(!utilBigendCalled)
    {
        utilBigendCalled = 1;
        data.i           = 0;
        data.chars[0]    = '\1';

        if(data.i == 1)
            utilBigendian = ajFalse;
        else
            utilBigendian = ajTrue;
    }

    return utilBigendian;
}
