_unmarshal_lzxc_reset_table(unsigned char **pData,
                                       unsigned int *pDataLen,
                                       struct chmLzxcResetTable *dest)
{

    if (*pDataLen != _CHM_LZXC_RESETTABLE_V1_LEN)
        return 0;


    _unmarshal_uint32    (pData, pDataLen, &dest->version);
    _unmarshal_uint32    (pData, pDataLen, &dest->block_count);
    _unmarshal_uint32    (pData, pDataLen, &dest->unknown);
    _unmarshal_uint32    (pData, pDataLen, &dest->table_offset);
    _unmarshal_uint64    (pData, pDataLen, &dest->uncompressed_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->compressed_len);
    _unmarshal_uint64    (pData, pDataLen, &dest->block_len);


    if (dest->version != 2)
        return 0;

    return 1;
}
