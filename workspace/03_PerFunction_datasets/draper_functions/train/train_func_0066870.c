ast_data_iterator_end(struct ast_data_iterator *iterator)
{

	if (iterator->last) {
		ao2_ref(iterator->last, -1);
	}


	if (iterator->is_pattern) {
		regfree(&(iterator->regex_pattern));
	}

	ao2_iterator_destroy(&(iterator->internal_iterator));

	ast_free(iterator);
	iterator = NULL;
}
