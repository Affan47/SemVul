sys_addhist(int phase)
{
    int i, j, phasewas = sys_histphase;
    double newtime = sys_getrealtime();
    int msec = (newtime - sys_histtime) * 1000.;
    for (j = NBIN-1; j >= 0; j--)
    {
        if (msec >= sys_bin[j])
        {
            sys_histogram[phasewas][j]++;
            break;
        }
    }
    sys_histtime = newtime;
    sys_histphase = phase;
    return (phasewas);
}
