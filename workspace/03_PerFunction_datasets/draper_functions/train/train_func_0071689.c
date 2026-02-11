make_new_name_for_module(Module_table *mpt)
{
    Module_table  *org_mpt;
    char          *new_name;
    unsigned int  length,length_add;
    int           i, t = 1, ver = 0;

    for(org_mpt = mpt; org_mpt->deriv_prev; org_mpt = org_mpt->deriv_prev);
    ver = org_mpt->copy_count;

    length = strlen(org_mpt->name);
#ifdef NAME_ADD_CN
    ver++;
#if 0
    for (i = 1; ; i++) {
        if (ver / (int)pow(10, i) == 0) {
            length_add = i;
            break;
        }
    }
#else
    for (i = 1; ; i++) {
        t = t * 10;
        if (ver < t)
            break;
    }
    length_add = i;

#endif
    length_add = length_add + 3;

    new_name = (char *)calloc(length+length_add, sizeof(char));
    if(new_name == NULL){
	fatal("No more room for a new name.\n");
    }
    sprintf(new_name, "%s_c%d", org_mpt->name, ver);
#else
    for(i = 1;; i++){
	if(ver/(int)pow((float)26, (float)i) == 0){
	    length_add = i;
	    break;
	}
    }
    new_name = (char *)calloc(length+length_add+1, sizeof(char));
    if(new_name == NULL){
	fatal("No more room for a new name.\n");
    }
    strncpy(new_name, org_mpt->name, length);
    for(i = length_add; i >= 2; i--){
	new_name[length+length_add-i] =
	    'a' + (ver/(int)pow((float)26, (float)(i-1)-1));
	ver -= (int)pow((float)26, (float)(i-1));
    }
    new_name[length+length_add-1] = 'a' + (ver % 26);
    new_name[length+length_add] = '\0';
#endif
    return(new_name);
}
