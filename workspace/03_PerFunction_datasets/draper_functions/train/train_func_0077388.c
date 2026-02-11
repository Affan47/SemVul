unpack_snps(const snp_t *packed_snps, unsigned char *unpacked_snps, size_t num_cols)
{
    int index;
    int packed_left;


    int32_t *unpacked_snps_p = (int32_t *) unpacked_snps;
    int i;
    int packed_length = num_cols / 4;
    for(i = 0; i < packed_length; i++)
    {
        *unpacked_snps_p = snp_lookup[ packed_snps[ i ] ].snp_block;
        unpacked_snps_p += 1;
    }


    index = packed_length * 4;
    packed_left = num_cols % 4;
    for(i = 0; i < packed_left; i++)
    {
        unpacked_snps[ index + i ] = snp_lookup[ packed_snps[ packed_length ] ].snp_array[ i ];
    }
}
