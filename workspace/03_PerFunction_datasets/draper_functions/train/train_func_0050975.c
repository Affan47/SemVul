ensMarkerDel(EnsPMarker *Pmarker)
{
    EnsPMarkermaplocation mml = NULL;

    EnsPMarkersynonym ms = NULL;

    EnsPMarker pthis = NULL;

    if (!Pmarker)
        return;

#if defined(AJ_DEBUG) && AJ_DEBUG >= 1
    if (ajDebugTest("ensMarkerDel"))
    {
        ajDebug("ensMarkerDel\n"
                "  *Pmarker %p\n",
                *Pmarker);

        ensMarkerTrace(*Pmarker, 1);
    }
#endif

    if (!(pthis = *Pmarker) || --pthis->Use)
    {
        *Pmarker = NULL;

        return;
    }

    ajStrDel(&pthis->PrimerLeft);
    ajStrDel(&pthis->PrimerRight);

    ensMarkersynonymDel(&pthis->Displaysynonym);

    while (ajListPop(pthis->Markersynonyms, (void **) &ms))
        ensMarkersynonymDel(&ms);

    ajListFree(&pthis->Markersynonyms);

    while (ajListPop(pthis->Markermaplocations, (void **) &mml))
        ensMarkermaplocationDel(&mml);

    ajListFree(&pthis->Markermaplocations);

    ajMemFree((void **) Pmarker);

    return;
}
