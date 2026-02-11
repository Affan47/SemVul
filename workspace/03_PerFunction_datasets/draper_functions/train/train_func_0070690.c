gs_free_const_bytestring(gs_memory_t *mem, gs_const_bytestring *pbs,
                         client_name_t cname)
{
    if (pbs->bytes)
        gs_free_const_object(mem, pbs->bytes, cname);
    else
        gs_free_const_string(mem, pbs->data, pbs->size, cname);
}
