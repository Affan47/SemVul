ajFileReopenNext(AjPFile file)
{
    static AjPStr name = NULL;

    if(!file->List)
    {
        ajDebug("ajFileReopenNext for non-list file %F\n", file);
        return ajFalse;
    }

    ajDebug("ajFileReopenNext for non-list file %F name '%S'\n",
            file, file->Name);


    if(!ajListPop(file->List, (void*) &name))
    {

        ajDebug("ajFileReopenNext failed - list completed\n");

        return ajFalse;
    }

    ajDebug("ajFileReopenNext filename '%S'\n", name);

    if(!ajFileReopenName(file, name))
    {

        ajStrDel(&name);

        return ajFalse;
    }


    ajStrDel(&name);
    file->End = ajFalse;

    ajDebug("ajFileNext success\n");

    return ajTrue;
}
