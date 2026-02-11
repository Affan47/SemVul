vbytes(int n, int mode)
{
    switch(mode)
    {
        case VDOUBLE: return(n*sizeof(double));
        case VINT:    return(n*sizeof(INT));
        case VCHAR:   return(n);
        case VARGL:   return(n*sizeof(carg));
        case VPREP:   return(sizeof(pplot));
        case VARC:    return(n*sizeof(arstruct));
        case VVARI:   return(n*sizeof(vari));
        case VXYZ:    return(n*sizeof(plxyz));
    }
    ERROR(("unknown mode %d in vbytes",mode));
    return(0);
}
