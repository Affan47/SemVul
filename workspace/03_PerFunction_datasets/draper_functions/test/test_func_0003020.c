print_epfpresunit(unsigned long unit)
{
    int chpr = 0;

    print_startvalue();
    switch(unit)
    {
        case 1: chpr += printf("no units"); break;
        case 2: chpr += printf("per meter"); break;
        case 3: chpr += printf("per cm"); break;
        case 4: chpr += printf("per mm"); break;
        case 5: chpr += printf("per um"); break;
        default: chpr += printf("undefined"); break;
    }
    print_endvalue();
    setcharsprinted(chpr);
}
