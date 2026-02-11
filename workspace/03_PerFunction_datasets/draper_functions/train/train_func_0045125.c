ajFeattypeGetInternalProt(const AjPStr type)
{
    if(!FeatInitDone)
	featInit();

    return featTableTypeInternal(type, FeatTypeTableProtein);
}
