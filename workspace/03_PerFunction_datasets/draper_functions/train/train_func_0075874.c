TimeStringToSecs(const std::string& timestring)
{
    uint32 secs       = 0;
    uint32 buffer     = 0;
    uint32 multiplier = 0;

    for(std::string::const_iterator itr = timestring.begin(); itr != timestring.end(); itr++ )
    {
        if(isdigit(*itr))
        {
            buffer*=10;
            buffer+= (*itr)-'0';
        }
        else
        {
            switch(*itr)
            {
                case 'd': multiplier = DAY;     break;
                case 'h': multiplier = HOUR;    break;
                case 'm': multiplier = MINUTE;  break;
                case 's': multiplier = 1;       break;
                default : return 0;
            }
            buffer*=multiplier;
            secs+=buffer;
            buffer=0;
        }
    }

    return secs;
}
