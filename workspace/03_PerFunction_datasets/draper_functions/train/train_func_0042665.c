test_unpack_snps(void **state)
{
    int i;

    unsigned char packed_snps[] = { 0x78 };
    snp_t unpacked_snps[4];
    unpack_snps( packed_snps, unpacked_snps, 4 );

    for(i = 0; i < 4; i++)
    {
        assert_int_equal( unpacked_snps[ i ], i );
    }
}
