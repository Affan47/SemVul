datalistconcat(Datalist* dl1, Datalist* dl2)
{
    Constant* vector;
    ASSERT(dl1 != NULL);
    if(dl2 == NULL) return dl1;
    vector = (Constant*)erealloc(dl1->data,sizeof(Constant)*(dl1->length+dl2->length));
    if(vector == NULL) return NULL;
    memcpy((void*)(vector+dl1->length),dl2->data,sizeof(Constant)*(dl2->length));
    dl1->data = vector;
    return dl1;
}
