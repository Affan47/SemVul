loadDisplayResources(struct display *d)
{
    int i, ret;
    void **ent;

    if (Setjmp(cnftalk.errjmp))
        return -1;
    if ((ret = startConfig(GC_gDisplay, &d->cfg.dep, False)) <= 0)
        return ret;
    gSendStr(d->name);
    gSendStr(d->class2);
    loadResources(&d->cfg);


    ret = 1;
    for (i = 0; i < as(dpyVal); i++) {
        if (!(ent = findCfgEnt(d, dpyVal[i].id)))
            ret = -1;
        else
            applyResource(dpyVal[i].id, ent,
                          (void **)(((char *)d) + dpyVal[i].off));
    }
    if (ret < 0)
        logError("Internal error: config reader supplied incomplete data\n");
    return ret;
}
