hdb_replace_extension(krb5_context context,
		      hdb_entry *entry,
		      const HDB_extension *ext)
{
    HDB_extension *ext2;
    HDB_extension *es;
    int ret;

    ext2 = NULL;

    if (entry->extensions == NULL) {
	entry->extensions = calloc(1, sizeof(*entry->extensions));
	if (entry->extensions == NULL) {
	    krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	    return ENOMEM;
	}
    } else if (ext->data.element != choice_HDB_extension_data_asn1_ellipsis) {
	ext2 = hdb_find_extension(entry, ext->data.element);
    } else {


	Der_class replace_class, list_class;
	Der_type replace_type, list_type;
	unsigned int replace_tag, list_tag;
	size_t size;
	size_t i;

	ret = der_get_tag(ext->data.u.asn1_ellipsis.data,
			  ext->data.u.asn1_ellipsis.length,
			  &replace_class, &replace_type, &replace_tag,
			  &size);
	if (ret) {
	    krb5_set_error_message(context, ret, "hdb: failed to decode "
				   "replacement hdb extention");
	    return ret;
	}

	for (i = 0; i < entry->extensions->len; i++) {
	    HDB_extension *ext3 = &entry->extensions->val[i];

	    if (ext3->data.element != choice_HDB_extension_data_asn1_ellipsis)
		continue;

	    ret = der_get_tag(ext3->data.u.asn1_ellipsis.data,
			      ext3->data.u.asn1_ellipsis.length,
			      &list_class, &list_type, &list_tag,
			      &size);
	    if (ret) {
		krb5_set_error_message(context, ret, "hdb: failed to decode "
				       "present hdb extention");
		return ret;
	    }

	    if (MAKE_TAG(replace_class,replace_type,replace_type) ==
		MAKE_TAG(list_class,list_type,list_type)) {
		ext2 = ext3;
		break;
	    }
	}
    }

    if (ext2) {
	free_HDB_extension(ext2);
	ret = copy_HDB_extension(ext, ext2);
	if (ret)
	    krb5_set_error_message(context, ret, "hdb: failed to copy replacement "
				   "hdb extention");
	return ret;
    }

    es = realloc(entry->extensions->val,
		 (entry->extensions->len+1)*sizeof(entry->extensions->val[0]));
    if (es == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }
    entry->extensions->val = es;

    ret = copy_HDB_extension(ext,
			     &entry->extensions->val[entry->extensions->len]);
    if (ret == 0)
	entry->extensions->len++;
    else
	krb5_set_error_message(context, ret, "hdb: failed to copy new extension");

    return ret;
}
