ajListExit(void)
{
    ajulong i = 0UL;

#ifdef AJ_SAVESTATS
    ajDebug("List usage : %d opened, %d closed, %Ld maxsize %Ld nodes\n",
            listNewCnt, listDelCnt, listMaxNum, listNodeCnt);
    ajDebug("List iterator usage : %d opened, %d closed\n",
            listIterNewCnt, listIterDelCnt);
#endif
    if(listFreeNext)
        for(i = 0UL; i < listFreeNext; i++)
            AJFREE(listFreeSet[i]);


    if(listFreeSet)
        AJFREE(listFreeSet);

    listFreeNext = 0UL;
    listFreeMax  = 0UL;

    return;
}
