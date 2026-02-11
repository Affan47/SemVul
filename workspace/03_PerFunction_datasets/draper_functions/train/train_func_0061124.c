gpt_printName(uint16_t name[], const char* msg)
{
    char *namestr;

    namestr = (char*)cli_utf16toascii((char*)name, 72);
    cli_dbgmsg("%s: %s\n", msg, namestr);

    free(namestr);
}
