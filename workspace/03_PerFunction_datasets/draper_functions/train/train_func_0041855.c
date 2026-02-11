ensExternaldatabaseDel(EnsPExternaldatabase *Pedb)
{
    EnsPExternaldatabase pthis = NULL;

    if (!Pedb)
        return;

#if defined(AJ_DEBUG) && AJ_DEBUG >= 1
    if (ajDebugTest("ensExternaldatabaseDel"))
    {
        ajDebug("ensExternaldatabaseDel\n"
                "  *Pedb %p\n",
                *Pedb);

        ensExternaldatabaseTrace(*Pedb, 1);
    }
#endif

    if (!(pthis = *Pedb) || --pthis->Use)
    {
        *Pedb = NULL;

        return;
    }

    ajStrDel(&pthis->Name);
    ajStrDel(&pthis->Release);
    ajStrDel(&pthis->Displayname);
    ajStrDel(&pthis->Secondaryname);
    ajStrDel(&pthis->Secondarytable);
    ajStrDel(&pthis->Description);

    ajMemFree((void **) Pedb);

    return;
}
