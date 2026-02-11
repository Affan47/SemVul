listFreeSetExpand(void)
{
    ajulong newsize;

    if(!listFreeSet)
    {
        listFreeMax = 1024;
        AJCNEW0(listFreeSet,listFreeMax);

        return;
    }

    if(listFreeMax >= 65536)
        return;

    newsize = listFreeMax + listFreeMax;
    AJCRESIZE0(listFreeSet, (size_t) listFreeMax, (size_t) newsize);
    listFreeMax = newsize;

    return;
}
