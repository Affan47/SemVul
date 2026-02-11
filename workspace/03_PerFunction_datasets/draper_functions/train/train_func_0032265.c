asn1_expect_algo(fmap_t *map, const void **asn1data, unsigned int *asn1len, unsigned int algo_size, const void *algo) {
    struct cli_asn1 obj;
    unsigned int avail;
    int ret;
    if((ret = asn1_expect_objtype(map, *asn1data, asn1len, &obj, 0x30)))
	return ret;
    avail = obj.size;
    *asn1data = obj.next;

    if((ret = asn1_expect_obj(map, &obj.content, &avail, 0x06, algo_size, algo)))
	return ret;
    if(avail && (ret = asn1_expect_obj(map, &obj.content, &avail, 0x05, 0, NULL)))
	return ret;
    if(avail) {
	cli_dbgmsg("asn1_expect_algo: extra data found in SEQUENCE\n");
	return 1;
    }
    return 0;
}
