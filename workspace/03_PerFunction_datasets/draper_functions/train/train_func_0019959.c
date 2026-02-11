do_cflag ( unsigned int a, unsigned int b, unsigned int c )
{
    unsigned int rc;

    cpsr&=~CPSR_C;
    rc=(a&0x7FFFFFFF)+(b&0x7FFFFFFF)+c;
    rc = (rc>>31)+(a>>31)+(b>>31);
    if(rc&2) cpsr|=CPSR_C;
}
