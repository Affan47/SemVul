writes(uint8_t *string)
{
    register uint8_t *s = string;

    if(s != NULL)
    {
        while(*s)
        {
            writec(*s);
            s++;
        }
    }
}
