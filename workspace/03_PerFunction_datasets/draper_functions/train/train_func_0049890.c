destroy_zend_class(zend_class_entry **pce)
{
	zend_class_entry *ce = *pce;

	if (--ce->refcount > 0) {
		return;
	}
	switch (ce->type) {
		case ZEND_USER_CLASS:
			if (ce->default_properties_table) {
				int i;

				for (i = 0; i < ce->default_properties_count; i++) {
					if (ce->default_properties_table[i]) {
						zval_ptr_dtor(&ce->default_properties_table[i]);
				    }
				}
				efree(ce->default_properties_table);
			}
			if (ce->default_static_members_table) {
				int i;

				for (i = 0; i < ce->default_static_members_count; i++) {
					if (ce->default_static_members_table[i]) {
						zval_ptr_dtor(&ce->default_static_members_table[i]);
					}
				}
				efree(ce->default_static_members_table);
			}
			zend_hash_destroy(&ce->properties_info);
			str_efree(ce->name);
			zend_hash_destroy(&ce->function_table);
			zend_hash_destroy(&ce->constants_table);
			if (ce->num_interfaces > 0 && ce->interfaces) {
				efree(ce->interfaces);
			}
			if (ce->info.user.doc_comment) {
				efree((char*)ce->info.user.doc_comment);
			}

			_destroy_zend_class_traits_info(ce);

			efree(ce);
			break;
		case ZEND_INTERNAL_CLASS:
			if (ce->default_properties_table) {
				int i;

				for (i = 0; i < ce->default_properties_count; i++) {
					if (ce->default_properties_table[i]) {
						zval_internal_ptr_dtor(&ce->default_properties_table[i]);
					}
				}
				free(ce->default_properties_table);
			}
			if (ce->default_static_members_table) {
				int i;

				for (i = 0; i < ce->default_static_members_count; i++) {
					zval_internal_ptr_dtor(&ce->default_static_members_table[i]);
				}
				free(ce->default_static_members_table);
			}
			zend_hash_destroy(&ce->properties_info);
			str_free(ce->name);
			zend_hash_destroy(&ce->function_table);
			zend_hash_destroy(&ce->constants_table);
			if (ce->num_interfaces > 0) {
				free(ce->interfaces);
			}
			free(ce);
			break;
	}
}
