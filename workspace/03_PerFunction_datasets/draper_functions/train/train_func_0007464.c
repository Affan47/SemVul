DemoVersionDescription(int version)
{
    static char resultbuf[16];

    switch (version)
    {
        case 104:
            return "v1.4";
        case 105:
            return "v1.5";
        case 106:
            return "v1.6/v1.666";
        case 107:
            return "v1.7/v1.7a";
        case 108:
            return "v1.8";
        case 109:
            return "v1.9";
        default:
            break;
    }


    if (version >= 0 && version <= 4)
    {
        return "v1.0/v1.1/v1.2";
    }
    else
    {
        sprintf(resultbuf, "%i.%i (unknown)", version / 100, version % 100);
        return resultbuf;
    }
}
