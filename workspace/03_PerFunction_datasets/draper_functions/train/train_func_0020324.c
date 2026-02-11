IMInitHash(w)
Widget w;
{
    IMIM **impp;
    IMIC **icpp;
    int i;

    impp = IM_IMHASH(w);
    icpp = IM_ICHASH(w);
    for (i = 0; i < IM_HASH_SIZE; i++) impp[i] = NULL;
    for (i = 0; i < IC_HASH_SIZE; i++) icpp[i] = NULL;
    IM_LASTIMID(w) = IM_LASTICID(w) = 0;
}
