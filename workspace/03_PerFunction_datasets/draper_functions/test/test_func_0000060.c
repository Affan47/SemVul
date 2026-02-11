groupncid(Symbol* sym)
{
#ifdef USE_NETCDF4
    if(usingclassic) {
        return "ncid";
    } else {
        char* grptmp;
	const char* tmp1;
        if(sym == NULL) return groupncid(rootgroup);
        ASSERT(sym->objectclass == NC_GRP);
        tmp1 = cname(sym);
        grptmp = poolalloc(strlen(tmp1)+strlen("_grp")+1);
        strcpy(grptmp,tmp1);
        strcat(grptmp,"_grp");
        return grptmp;
    }
#else
    return "ncid";
#endif
}
