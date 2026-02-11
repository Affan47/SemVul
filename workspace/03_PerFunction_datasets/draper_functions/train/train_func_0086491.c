SrcUD(float X[], double dt, double Time,
                 int Nwing, double LpScl,
                 float Imp[], float ImpD[], boolean Interp)
{
    mem_float *Xp;
    fast_float v;

    double dh;
    long iTime = (long) Time;

    dh = MIN(Npc, Npc/dt);

    Xp = &X[iTime];
    v = FilterUD(Imp, ImpD, Nwing, Interp, Xp, Time - iTime,
                 -1, dh);
    v += FilterUD(Imp, ImpD, Nwing, Interp, Xp+1, (1 + iTime) - Time,
                  1, dh);
    v *= LpScl;
    return (float) v;
}
