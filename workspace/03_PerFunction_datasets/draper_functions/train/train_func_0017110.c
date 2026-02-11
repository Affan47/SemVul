icd_vdd(void)
{
    unsigned int vdd=0;

    if(icd_fd<0) return 0.0;

    vdd=icd_cmd("$$701C\r");

    return ((double)vdd) / 40.0;
}
