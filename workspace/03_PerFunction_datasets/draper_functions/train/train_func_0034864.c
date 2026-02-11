ajListIterNewread(const AjPList list)
{
    AjIList iter = NULL;

    if(!list)
        return NULL;

    AJNEW0(iter);
    iter->ReadHead = list;
    iter->Back = ajFalse;
    iter->Here = list->First;
    iter->Modify = ajFalse;

#ifdef AJ_SAVESTATS
    listIterNewCnt++;
#endif

    return iter;
}
