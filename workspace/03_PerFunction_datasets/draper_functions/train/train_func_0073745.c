ensMapperDel(EnsPMapper *Pmapper)
{
    EnsPMapper pthis = NULL;

    if (!Pmapper)
        return;

#if defined(AJ_DEBUG) && AJ_DEBUG >= 1
    if (ajDebugTest("ensMapperDel"))
    {
        ajDebug("ensMapperDel\n"
                "  *Pmapper %p\n",
                *Pmapper);

        ensMapperTrace(*Pmapper, 1);
    }
#endif

    if (!(pthis = *Pmapper) || --pthis->Use)
    {
        *Pmapper = NULL;

        return;
    }

    ajTableDel(&pthis->Mapperpairs);

    ajStrDel(&pthis->TypeSource);
    ajStrDel(&pthis->TypeTarget);

    ensCoordsystemDel(&pthis->CoordsystemSource);
    ensCoordsystemDel(&pthis->CoordsystemTarget);

    ajMemFree((void **) Pmapper);

    return;
}
