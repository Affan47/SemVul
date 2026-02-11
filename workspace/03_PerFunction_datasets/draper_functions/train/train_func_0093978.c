save_to_file(VMG_ class CVmFile *fp)
{
    unsigned long rem;
    unsigned long idx;


    fp->write_int4(get_element_count());


    for (idx = 1, rem = get_element_count() ; rem != 0 ; )
    {
        size_t avail;
        size_t chunk;
        unsigned char *p;


        p = get_ele_ptr(idx, &avail);


        chunk = avail;
        if (chunk > rem)
            chunk = (size_t)rem;


        fp->write_bytes((char *)p, chunk);


        idx += chunk;
        rem -= chunk;
    }
}
