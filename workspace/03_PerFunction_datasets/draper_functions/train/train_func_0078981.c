print_whitebalance(unsigned long mode)
{
    int chpr = 0;

    print_startvalue();
    switch(mode)
    {
        case 0: chpr += printf("Auto"); break;
        case 1: chpr += printf("Manual"); break;
        default: chpr += printf("???"); break;
    }
    print_endvalue();
    setcharsprinted(chpr);
}
