GetFileFromAllWithPacketN(uint32_t packageNum,uint32_t filectime)
{
    GSList *tlist;

    tlist = prlist;
    while (tlist) {
        if( (((FileInfo *)tlist->data)->packetn == packageNum)
                && ((((FileInfo *)tlist->data)->filenum == filectime) ) )
                    break;
            tlist = g_slist_next(tlist);
    }
    if (tlist != NULL)
            return (FileInfo *)(tlist ? tlist->data : NULL);
    tlist =  pblist ;
    while (tlist) {
         if( (((FileInfo *)tlist->data)->packetn == packageNum)
                && ((((FileInfo *)tlist->data)->filenum == filectime) ) )
                    break;
            tlist = g_slist_next(tlist);
    }
    return (FileInfo *)(tlist ? tlist->data : NULL);
}
