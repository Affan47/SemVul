Replace(tHeapElement *e){
    int i=e->hID;

    if(i<0 || this != e->Heap())
        tERR_ERROR_INT("Element is not in this heap! (Note: this usually is a followup error when the system fails to recover from another error. When reporting, please also include whatever happened before this.)");

    Replace(i);

#ifdef EVENT_DEB
    CheckHeap();
#endif
}
