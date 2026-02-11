seqMsfDataDel(SeqPMsfData* pthys)
{
    SeqPMsfData thys;
    ajuint i;

    if(!pthys)
        return;

    if(!*pthys)
        return;

    thys = *pthys;

    ajDebug("seqMsfDataDel Nseq:%u Count:%u Table:%u Nexus:%Lu\n",
            thys->Nseq, thys->Count, ajTableGetLength(thys->Table),
            ajNexusGetNtaxa(thys->Nexus));

    for(i=0; i < thys->Nseq; i++)
    {
        ajStrDel(&thys->Names[i]);
    }


    AJFREE(thys->Names);

    ajNexusDel(&thys->Nexus);
    ajStrDel(&thys->Gene);
    ajStrDel(&thys->Domain);
    ajStrDel(&thys->NextGene);
    ajStrDel(&thys->NextDomain);
    ajTableMapDel(thys->Table, &seqMsfTabDel, NULL);
    ajTableFree(&thys->Table);

    AJFREE(*pthys);

    return;
}
