sha224_init(SHAobject *sha_info)
{
    TestEndianness(sha_info->Endianness)
    sha_info->digest[0] = 0xc1059ed8L;
    sha_info->digest[1] = 0x367cd507L;
    sha_info->digest[2] = 0x3070dd17L;
    sha_info->digest[3] = 0xf70e5939L;
    sha_info->digest[4] = 0xffc00b31L;
    sha_info->digest[5] = 0x68581511L;
    sha_info->digest[6] = 0x64f98fa7L;
    sha_info->digest[7] = 0xbefa4fa4L;
    sha_info->count_lo = 0L;
    sha_info->count_hi = 0L;
    sha_info->local = 0;
    sha_info->digestsize = 28;
}
