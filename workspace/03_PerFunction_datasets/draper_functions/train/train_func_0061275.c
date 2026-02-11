md5_draw_frame (vo_instance_t * _instance,
			    uint8_t * const * buf, void * id)
{
    pgm_instance_t * instance = (pgm_instance_t *) _instance;
    unsigned int offset;
    char * p;
    int padding;

    instance->md5_hash[0] = 0x67452301;
    instance->md5_hash[1] = 0xefcdab89;
    instance->md5_hash[2] = 0x98badcfe;
    instance->md5_hash[3] = 0x10325476;
    instance->md5_bytes = 0;

    internal_draw_frame (instance, buf);

    offset = instance->md5_bytes & 0x3f;
    p = (char *)instance->md5_block + offset;
    padding = 55 - offset;

    *p++ = 0x80;
    if (padding < 0) {
	memset (p, 0, padding + 8);
	little_endian (instance->md5_block, 16);
	md5_transform (instance->md5_hash, instance->md5_block);
	p = (char *)instance->md5_block;
	padding = 56;
    }

    memset (p, 0, padding);
    instance->md5_block[14] = instance->md5_bytes << 3;
    instance->md5_block[15] = instance->md5_bytes >> 29;
    little_endian (instance->md5_block, 14);
    md5_transform (instance->md5_hash, instance->md5_block);

    printf ("%08x%08x%08x%08x *%d.pgm\n", swap (instance->md5_hash[0]),
	    swap (instance->md5_hash[1]) , swap (instance->md5_hash[2]),
	    swap (instance->md5_hash[3]), instance->framenum++);
}
