last_intstack
#ifdef KC_USE_PROTOTYPES
(intstack kc_p)
#else
(kc_p) intstack kc_p;
#endif
{	boolean kc_not_ready = True;
	int kc_tmp = (int)0;

	assert_intstack(kc_p,"kc_p");
	if (kc_p->prod_sel == sel_Nilintstack) {
		(void)fflush(stdout); (void)fprintf(stderr, kc_error_last_with_nil_argument, "intstack",  "intstack"); exit( 1 );
	}
	while(kc_not_ready) {

		assert_intstack(kc_p,"kc_p");
		if (kc_p->prod_sel == sel_Nilintstack) {
			kc_not_ready=False;
		} else if (kc_p->prod_sel == sel_Consintstack) {
			kc_tmp = kc_p->u.Consintstack.int_1;
			kc_p = kc_p->u.Consintstack.intstack_1;
		} else {
			kc_invalid_operator(kc_error_last, kc_phylum_intstack, __LINE__, __FILE__, (int)kc_p->prod_sel);
	}	}
	return kc_tmp;
}
