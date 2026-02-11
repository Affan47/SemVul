ovdb_ctl(OVCTLTYPE type, void *val)
{
    int *i;
    OVSORTTYPE *sorttype;
    bool *boolval;

    switch (type) {
    case OVSPACE:
        i = (int *)val;
        *i = -1;
        return true;
    case OVSORT:
        sorttype = (OVSORTTYPE *)val;
        *sorttype = OVNEWSGROUP;
        return true;
    case OVCUTOFFLOW:
        Cutofflow = *(bool *)val;
        return true;
    case OVSTATICSEARCH:
	i = (int *)val;
	*i = true;
	return true;
    case OVCACHEKEEP:
    case OVCACHEFREE:
        boolval = (bool *)val;
        *boolval = false;
        return true;
    default:
        return false;
    }
}
