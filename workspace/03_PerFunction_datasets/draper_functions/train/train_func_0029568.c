simple_itoa(unsigned int i)
{


    static char local[22];
    char *p = &local[21];
    *p-- = '\0';
    do{
        *p-- = '0' + i%10;
        i/=10;
    }while(i>0);
    return p+1;
}
