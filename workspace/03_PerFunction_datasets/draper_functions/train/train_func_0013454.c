REMflush()
{
    int		i;

    if (REMbuffptr == REMbuffer) return TRUE;
    i = xwrite(ToServer, REMbuffer, (int)(REMbuffptr - REMbuffer));
    REMbuffptr = REMbuffer;
    return i < 0 ? FALSE : TRUE;
}
