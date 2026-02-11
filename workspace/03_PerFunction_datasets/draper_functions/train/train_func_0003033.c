kc_ht_dec_level
#ifdef KC_USE_PROTOTYPES
(kc_storageclass_t kc_a_storageclass_t)
#else
(kc_a_storageclass_t) kc_storageclass_t kc_a_storageclass_t;
#endif
{
	int kc_i, kc_j, kc_m;
	kc_hashtableentry_t* kc_hte;

	kc_hashtable_t kc_a_hashtable_t = kc_hashtables[(int)kc_a_storageclass_t];
	if (kc_a_hashtable_t->dynamic_malloc_private_data != 0) {
		kc_a_hashtable_t->dec_dynamic_malloc_private_data = kc_a_hashtable_t->dynamic_malloc_private_data;
		kc_a_hashtable_t->dynamic_malloc_private_data = kc_a_hashtable_t->dynamic_malloc_private_data->next;
		for (kc_i=0; kc_i < kc_a_hashtable_t->size; kc_i++) {
			kc_m = (int)kc_ht_store_dynamic;
			kc_hte = &kc_a_hashtable_t->hashtable[kc_i][kc_m];
			for (kc_j=kc_hte->nr -1; kc_j >= 0; kc_j--) {
				kc_private_malloc_t kc_a_private_malloc_t = kc_a_hashtable_t->dec_dynamic_malloc_private_data;
				boolean kc_is_in_block = (*kc_a_hashtable_t->in_block)((kc_voidptr_t)kc_hte->index[kc_j].yt_casestring, kc_a_private_malloc_t->malloc_private_data);
#if 0
				while ((!kc_is_in_block) && kc_a_private_malloc_t->prev) {
					kc_a_private_malloc_t = kc_a_private_malloc_t->prev;
					kc_is_in_block = (*kc_a_hashtable_t->in_block)((kc_voidptr_t)kc_hte->index[kc_j].yt_casestring, kc_a_private_malloc_t->malloc_private_data);
				}
#endif
				if (kc_is_in_block) {
					kc_hte->nr--;
					kc_hte->index[kc_j] = kc_hte->index[kc_hte->nr];
					kc_hte->index[kc_hte->nr].yt_casestring = 0;
				}
#ifdef KC_SEPARATE_HASH_LEVELS
				  else {
					break;
				}
#endif
		}	}
	} else {


		assert(kc_zero_constant);
}	}
