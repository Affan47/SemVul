varith(z,name,status)
char *z, *name;
int status;
{ vari *v, *va;
    va = arbuild(z,0,strlen(z)-1,NULL,1,0);
    if (lf_error) return(NULL);
    v = vareval(va,0);
    deletevar(va);

    v = saveresult(v,name,status);
    return(v);
}
