ajListstrIterGetBack(AjIList iter)
{
    void* item = NULL;

    AjPListNode node = NULL;

    if(!iter)
        return NULL;

    node = iter->Here;

    if(!node->Prev)
        return NULL;

    if(!iter->Back)
    {
        item = node->Prev->Prev->Item;
        iter->Here = node->Prev->Prev;
        iter->Back = ajTrue;
    }
    else
    {
        item = node->Prev->Item;
        iter->Here = node->Prev;
    }

    return (AjPStr) item;
}
