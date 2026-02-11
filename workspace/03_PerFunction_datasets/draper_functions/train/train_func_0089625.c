genunf(ConstReal low, ConstReal high)


{
    static Real genunf;
    char msg[1000];

    if(!(low > high)) goto S10;
    sprintf(msg,"LOW > HIGH in GENUNF: LOW %16.6E HIGH: %16.6E\n",low,high);
    stop(msg);
S10:
    genunf = low+(high-low)*ranf();
    return genunf;
}
