iterate_entries(hx509_context context,
		struct p11_module *p, struct p11_slot *slot,
		CK_SESSION_HANDLE session,
		CK_ATTRIBUTE *search_data, int num_search_data,
		CK_ATTRIBUTE *query, int num_query,
		int (*func)(hx509_context,
			    struct p11_module *, struct p11_slot *,
			    CK_SESSION_HANDLE session,
			    CK_OBJECT_HANDLE object,
			    void *, CK_ATTRIBUTE *, int), void *ptr)
{
    CK_OBJECT_HANDLE object;
    CK_ULONG object_count;
    int ret, ret2, i;

    ret = P11FUNC(p, FindObjectsInit, (session, search_data, num_search_data));
    if (ret != CKR_OK) {
	return -1;
    }
    while (1) {
	ret = P11FUNC(p, FindObjects, (session, &object, 1, &object_count));
	if (ret != CKR_OK) {
	    return -1;
	}
	if (object_count == 0)
	    break;

	for (i = 0; i < num_query; i++)
	    query[i].pValue = NULL;

	ret = P11FUNC(p, GetAttributeValue,
		      (session, object, query, num_query));
	if (ret != CKR_OK) {
	    return -1;
	}
	for (i = 0; i < num_query; i++) {
	    query[i].pValue = malloc(query[i].ulValueLen);
	    if (query[i].pValue == NULL) {
		ret = ENOMEM;
		goto out;
	    }
	}
	ret = P11FUNC(p, GetAttributeValue,
		      (session, object, query, num_query));
	if (ret != CKR_OK) {
	    ret = -1;
	    goto out;
	}

	ret = (*func)(context, p, slot, session, object, ptr, query, num_query);
	if (ret)
	    goto out;

	for (i = 0; i < num_query; i++) {
	    if (query[i].pValue)
		free(query[i].pValue);
	    query[i].pValue = NULL;
	}
    }
 out:

    for (i = 0; i < num_query; i++) {
	if (query[i].pValue)
	    free(query[i].pValue);
	query[i].pValue = NULL;
    }

    ret2 = P11FUNC(p, FindObjectsFinal, (session));
    if (ret2 != CKR_OK) {
	return ret2;
    }

    return ret;
}
