mkunicodetable(void)
{
    int i;
    int thisstate;
    unsigned char need_block[256];
    int block;
    char buf[80];


    for (i = 0; i < 256; i++) {
	need_block[i] = 0;
    }
    for (i = 0; i < map_num; i++) {
	need_block[map[i].code>>8] = 1;
    }

    table_num = 0;

    printf("/* The next two tables are used for doing translations on\n");
    printf(" * 16-bit unicode values.  First look up the Unicode block\n");
    printf(" * (high-order byte) in the chartables_unicode_block table\n");
    printf(" * to find the index into chartables_unicode for that block.\n");
    printf(" * If the index is 255, there are no translations for that\n");
    printf(" * block, so characters can be encoded in UTF-8 algorithmically\n");
    printf(" * Otherwise, look up the low-order byte in the chartables_unicode\n");
    printf(" * using the index to select the state.\n");
    printf(" */\n");
    printf("const unsigned char chartables_unicode_block[256] = {");

    for (block = 0; block < 256; block++) {
	if (!(block & 0x7)) printf("\n");
	if (!need_block[block]) {
	    printf(" 255,");
	    continue;
	}

 	snprintf(buf, sizeof(buf), "BLOCK-%02x-INDEX-%d", block, table_num);
	thisstate = newstate(buf);
	printf(" %3d,", thisstate);

	for (i = 0; i < 256; i++) {
	    setcode(thisstate, i, (block << 8) + i);
	}
    }

    printf("\n};\n\n");

    printf("/* NOTE: Unlike other charset translation tables, the \n");
    printf(" * chartables_unicode table is NOT used to directly parse\n");
    printf(" * a charset.  See the comment on chartables_unicode_block\n");
    printf(" * for a descripton of how this table is used.\n");
    printf(" */\n");
}
