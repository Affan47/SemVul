ajListstrMap(AjPList list,
                  void (*apply)(AjPStr* str, void* cl), void* cl)
{
    AjPListNode rest = NULL;

    assert(apply);

    for(rest = list->First; rest->Next; rest = rest->Next)
        (*apply)((AjPStr*) &rest->Item, cl);

    return;
}
