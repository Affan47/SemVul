header_complex_find_entry(struct header_complex_index *thestuff,
                          void *theentry)
{
    struct header_complex_index *hciptr;

    for (hciptr = thestuff; hciptr != NULL && hciptr->data != theentry;
         hciptr = hciptr->next);
    return hciptr;
}
