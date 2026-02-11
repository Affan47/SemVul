buff_add  (char*  buff, char*  buffEnd, const char*  format, ... )
{
    int      avail;

    avail = (buffEnd - buff);

    if (avail > 0) {
        va_list  args;
        int      nn;

        va_start(args, format);
        nn = vsnprintf( buff, avail, format, args);
        va_end(args);

        if (nn < 0) {


            nn = avail;
        }
        else if (nn > avail) {
            nn = avail;
        }

        buff += nn;


        if (buff >= buffEnd)
            buff[-1] = 0;
        else
            buff[0] = 0;
    }
    return buff;
}
