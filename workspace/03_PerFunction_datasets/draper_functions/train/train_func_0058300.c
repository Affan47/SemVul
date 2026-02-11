hm_pair_test(const int delay){
	const char *key = "aaancdefgh";
	const char *val = "1234567890";

	hm_pair_t *p1 = hm_pair_create(key, val);
	hm_pair_t *p2 = hm_pair_createx(key, val, 1);

	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, key) == 0			);
	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, "~~~ non existent") < 0	);
	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, "!!! non existent") > 0	);

	PRINTF_TEST("hm_pair_t", "key",		strcmp(hm_pair_getkey(p1), key) == 0		);
	PRINTF_TEST("hm_pair_t", "val",		strcmp(hm_pair_getval(p1), val) == 0		);


	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p1)				);
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p2)				);

	if (delay){
	printf("sleep for 1 sec...\n");
	sleep(1);
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p1)				);
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p2) == 0				);
	}

	free(p1);
	free(p2);
}
