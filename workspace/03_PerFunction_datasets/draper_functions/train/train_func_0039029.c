aisc_server_dllint_2_bytestring(dllpublic_ext * pb,bytestring *bs,int offset)
{
    int *ptr;
    dllheader_ext * mh;
    if (bs->data) free(bs->data);
    bs->data = 0;
    bs->size = 0;
    if (pb->cnt == 0) return 0;

    bs->size = sizeof(int) * pb->cnt;
    ptr = (int *)malloc(bs->size);
    bs->data = (char *)ptr;

    for (mh=pb->first;mh;mh=mh->next) {
        *(ptr++) = *(int *) (((char *)mh)+offset);
    }
    return 0;
}
