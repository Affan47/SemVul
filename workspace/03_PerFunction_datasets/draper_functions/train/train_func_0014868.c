blob_list_prepend(blob_list_ty *lllp, blob_ty *llp)
{
    size_t          j;

    if (lllp->length >= lllp->maximum)
    {
        size_t          nbytes;

        lllp->maximum = lllp->maximum * 2 + 8;
        nbytes = lllp->maximum * sizeof(blob_ty *);
        lllp->list = mem_change_size(lllp->list, nbytes);
    }
    for (j = lllp->length; j > 0; --j)
        lllp->list[j] = lllp->list[j - 1];
    lllp->length++;
    lllp->list[0] = llp;
}
