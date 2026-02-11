List_sliceInPlace(List* self, long startIndex, long endIndex, long step)
{
    List *tmp = List_new();
    ssize_t cur;
    size_t i;

    size_t slicesize = abs((int)((step < 0)
                           ? (endIndex - startIndex + 1) / step + 1
                           : (endIndex - startIndex - 1) / step + 1));
    for(cur = startIndex, i = 0; i < slicesize; cur += step, i++)
    {
        List_append_(tmp, List_at_(self, cur));
    }

    List_copy_(self, tmp);
    List_free(tmp);
}
