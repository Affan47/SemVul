bv_delete(bv_ptr b)
{

    if(b==NULL || b->buffer==NULL)
        return(FAIL);


    HDfree(b->buffer);
    HDfree(b);

    return(SUCCEED);
}
