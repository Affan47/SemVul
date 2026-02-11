getInt(const char *param, int val, int min, int max, const char *description){
    if (helpflag){
        printf("    %s=%3i [%3i:%3i] %s\n",param,val,min,max,description);
        return 0;
    }
    int   i;
    char *s = 0;

    arb_assert(pargc >= 1);

    for (i=1;i<pargc;i++){
        s = pargv[i];
        if (*s == '-') s++;
        if (!strncasecmp(s,param,strlen(param))) break;
    }
    if (i==pargc) return val;
    s+= strlen(param);
    if (*s != '=') return val;
    s++;
    val = atoi(s);
    pargc--;
    for (;i<pargc;i++){
        pargv[i] = pargv[i+1];
    }

    if (val<min) val = min;
    if (val>max) val = max;
    return val;
}
