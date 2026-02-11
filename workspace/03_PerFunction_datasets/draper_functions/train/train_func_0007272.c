print_ulong(FILE *inptr,unsigned long count,unsigned short byteorder,
                unsigned long offset)
{
    int i,j;
    unsigned long value;
    int chpr = 0;

    if(count)
    {
        value = read_ulong(inptr,byteorder,offset);
        if(feof(inptr) || ferror(inptr))
        {
            clearerr(inptr);
            setcharsprinted(chpr);
            return;
        }
        if(PRINT_BOTH_VALUE)
            chpr += printf("%#lx/%lu",value,value);
        else if(PRINT_HEX_VALUE)
            chpr += printf("%#lx",value);
        else if(PRINT_DEC_VALUE)
            chpr += printf("%lu",value);
    }
    if(PRINT_MULTIVAL_ALL)
    {
        for(i = 1; i < count; ++i,offset += 4L)
        {
            value = read_ulong(inptr,byteorder,HERE);
            if(feof(inptr) || ferror(inptr))
            {
                clearerr(inptr);
                setcharsprinted(chpr);
                return;
            }
            if(PRINT_BOTH_VALUE)
                chpr += printf(",%#lx/%lu",value,value);
            else if(PRINT_HEX_VALUE)
                chpr += printf(",%#lx",value);
            else if(PRINT_DEC_VALUE)
                chpr += printf(",%lu",value);
        }
    }
    else
    {
#define MAX 3UL
        j = count > MAX + 2 ? MAX : count;
        for(i = 1; i < j; ++i,offset += 4L)
        {
            value = read_ulong(inptr,byteorder,HERE);
            if(feof(inptr) || ferror(inptr))
            {
                clearerr(inptr);
                setcharsprinted(chpr);
                return;
            }
            if(PRINT_BOTH_VALUE)
                chpr += printf(",%#lx/%lu",value,value);
            else if(PRINT_HEX_VALUE)
                chpr += printf(",%#lx",value);
            else if(PRINT_DEC_VALUE)
                chpr += printf(",%lu",value);
        }
        if(count > j)
        {
            chpr += printf(" ... ");
            offset += (unsigned long)(count - j) * 4L;
            value = read_ulong(inptr,byteorder,offset);
            if(feof(inptr) || ferror(inptr))
            {
                clearerr(inptr);
                setcharsprinted(chpr);
                return;
            }
            if(PRINT_BOTH_VALUE)
                chpr += printf(",%#lx/%lu (%lu)",value,value,count);
            else if(PRINT_HEX_VALUE)
                chpr += printf(",%#lx (%lu)",value,count);
            else if(PRINT_DEC_VALUE)
                chpr += printf(",%lu (%lu)",value,count);
            if(PRINT_ADDRESS)
                chpr += printf(" -> @%lu",offset);
        }
#undef MAX
    }
    setcharsprinted(chpr);
}
