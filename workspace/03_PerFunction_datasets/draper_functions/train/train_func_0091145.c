getProgramCounter(void)
{
    uchar *response;
    int responseSize;
    uchar command[] = { CMND_READ_PC };

    check(doJtagCommand(command, sizeof(command), response, responseSize),
	  "cannot read program counter");
    unsigned long result = b4_to_u32(response + 1);
    delete [] response;


    result *= 2;

    return result;
}
