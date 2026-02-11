test_chksum_large(void)
{
    uint32_t chksum;
    size_t u;


    for(u = 0; u < BUF_LEN; u++)
        large_buf[u] = u * 3;


    chksum = H5_checksum_fletcher32(large_buf, sizeof(large_buf));
    VERIFY(chksum, 0x85b4e2a, "H5_checksum_fletcher32");

    chksum = H5_checksum_crc(large_buf, sizeof(large_buf));
    VERIFY(chksum, 0xfbd0f7c0, "H5_checksum_crc");

    chksum = H5_checksum_lookup3(large_buf, sizeof(large_buf), 0);
    VERIFY(chksum, 0x1bd2ee7b, "H5_checksum_lookup3");


    HDmemset(large_buf, 0, sizeof(large_buf));
    chksum = H5_checksum_fletcher32(large_buf, sizeof(large_buf));
    VERIFY(chksum, 0, "H5_checksum_fletcher32");

    chksum = H5_checksum_crc(large_buf, sizeof(large_buf));
    VERIFY(chksum, 0xfac8b4c4, "H5_checksum_crc");

    chksum = H5_checksum_lookup3(large_buf, sizeof(large_buf), 0);
    VERIFY(chksum, 0x930c7afc, "H5_checksum_lookup3");
}
