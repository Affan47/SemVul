vrvec(v1,f)
vari *v1;
double (*f)();
{ vari *v;
    INT i, n;
    n = (INT)vitem(v1,0);
    v = createvar("_vrvec",STHIDDEN,n,VDOUBLE);
    if (lf_error) return(NULL);
    for (i=0; i<n; i++) vassn(v,i,f());
    deleteifhidden(v1);
    return(v);
}
