GetUINT(unsigned const char *buffer, int bigEndian)
{
    unsigned int result;

    if (bigEndian)
    {
        result = *buffer;
        result <<= 8;
        result += buffer[1];
    }
    else
    {
        result = buffer[1];
        result <<= 8;
        result += *buffer;
    }
    return result;
}
