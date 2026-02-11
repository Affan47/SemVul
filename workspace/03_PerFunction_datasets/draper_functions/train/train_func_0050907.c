kc_print_all_hashtable_statistics
#ifdef KC_USE_PROTOTYPES
(FILE *kc_f)
#else
(kc_f) FILE *kc_f;
#endif
{	kc_hashtable_t kc_a_hashtable_t = kc_all_hashtables;
	unsigned int kc_k;
	boolean kc_st_found;

	 if (kc_f == NULL) kc_f = stdout;
	do {
		kc_st_found = False;
		for (kc_k=0; kc_k < (int)kc_last_storageclass; kc_k++) {
			if (kc_hashtables[kc_k] == kc_a_hashtable_t) {
				kc_st_found = True;
				(void)fprintf(kc_f, "Information for storage class %s: \n", kc_storageclassnames[kc_k]);
		}	}
		if (! kc_st_found) {
			(void)fprintf(kc_f, "Information for unknown storage class: \n");
		}
		kc_print_hashtable_statistics(kc_f, kc_a_hashtable_t);
		kc_print_hashtable_memory_statistics(kc_f, kc_a_hashtable_t);
		kc_a_hashtable_t = kc_a_hashtable_t->next;
	} while(kc_a_hashtable_t != kc_all_hashtables);
}
