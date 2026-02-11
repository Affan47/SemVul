kc_growindex
#ifdef KC_USE_PROTOTYPES
(kc_hashtableentry_t *kc_hte, kc_hashtable_t kc_a_ht)
#else
(kc_hte, kc_a_ht) kc_hashtableentry_t *kc_hte; kc_hashtable_t kc_a_ht;
#endif
{	int kc_newsize = kc_hte->ibound + kc_a_ht->bucket_alloc_inc;
	if (kc_newsize == kc_a_ht->bucket_alloc_inc)
		kc_hte->index = (YYSTYPE *) (*kc_a_ht->bucket_calloc)((kc_size_t)kc_newsize, (kc_size_t)sizeof(YYSTYPE), kc_a_ht->bucket_alloc_private_data);
	else
		kc_hte->index = (YYSTYPE *) (*kc_a_ht->bucket_realloc)((kc_voidptr_t)kc_hte->index, (kc_size_t)kc_hte->ibound * sizeof(YYSTYPE), (kc_size_t)kc_newsize * sizeof(YYSTYPE), kc_a_ht->bucket_alloc_private_data);
	kc_hte->ibound = kc_newsize;
}
