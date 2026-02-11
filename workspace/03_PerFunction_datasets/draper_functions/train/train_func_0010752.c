uc_copyn(const char *pt,int len) {
    unichar_t *res, *rpt;

    if(!pt)
return((unichar_t *)0);

#ifdef MEMORY_MASK
    if ( (len+1)*sizeof(unichar_t)>=MEMORY_MASK )
	len = MEMORY_MASK/sizeof(unichar_t)-1;
#endif
    res = galloc((len+1)*sizeof(unichar_t));
    for ( rpt=res; --len>=0 ; *rpt++ = *(unsigned char *) pt++ );
    *rpt = '\0';
return(res);
}
