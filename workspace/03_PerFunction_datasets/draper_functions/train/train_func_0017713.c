FirstElement(List *l)
{
    if (l == NULL) {
        NullPtrError("FirstElement");
        return NULL;
    }
    if (l->Flags&CONTAINER_READONLY) {
        ErrorReadOnly(l,"FirstElement");
        return NULL;
    }
    return l->First;
}
