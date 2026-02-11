del_infilepos_nddata(APTR data)
{
    INFILEPOS *pos = (INFILEPOS *) data;

    if (pos)
    {

        (pos->inpf->pos_count)--;

        D(fprintf(stderr, DINF "del pos-req: \"%s\" (%lu,%lu); %lu left\n",
               pos->inpf->filename ? pos->inpf->filename : (STRPTR) "STDIN",
                  pos->x, pos->y, pos->inpf->pos_count));


        ufree(pos);
    }
}
