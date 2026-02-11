_ojc_set_key(ojcVal val, const char *key, int klen) {
    struct _MList	freed_bstrs = { 0, 0 };

    free_key(val, &freed_bstrs);
    pthread_mutex_lock(&free_mutex);
    if (0 != freed_bstrs.head) {
	if (0 == free_bstrs.head) {
	    free_bstrs.head = freed_bstrs.head;
	} else {
	    free_bstrs.tail->next = freed_bstrs.head;
	}
	free_bstrs.tail = freed_bstrs.tail;
    }
    pthread_mutex_unlock(&free_mutex);

    if (0 != key) {
	if (0 >= klen) {
	    klen = strlen(key);
	}
	if ((int)sizeof(union _Bstr) <= klen) {
	    val->key_type = STR_PTR;
	    val->key.str = strndup(key, klen);
	    val->key.str[klen] = '\0';
	} else if ((int)sizeof(val->key.ca) <= klen) {
	    val->key_type = STR_BLOCK;
	    val->key.bstr = _ojc_bstr_create();
	    memcpy(val->key.bstr->ca, key, klen);
	    val->key.bstr->ca[klen] = '\0';
	} else {
	    val->key_type = STR_ARRAY;
	    memcpy(val->key.ca, key, klen);
	    val->key.ca[klen] = '\0';
	}
    }
}
