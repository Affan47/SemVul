Read16BitsHighLow(FILE * fp)
{
    int     first, second, result;


    first = 0xff & getc(fp);


    second = 0xff & getc(fp);


    result = (first << 8) + second;


#ifndef	THINK_C42
    if (result & 0x8000)
        result = result - 0x10000;
#endif
    return (result);
}
