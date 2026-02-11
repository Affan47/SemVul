Conv_ALuint_ALdouble(ALdouble val)
{
    if(val > 1.0) return 4294967295u;
    if(val < -1.0) return 0;
    return (ALint)(val * 2147483647.0) + 2147483648u;
}
