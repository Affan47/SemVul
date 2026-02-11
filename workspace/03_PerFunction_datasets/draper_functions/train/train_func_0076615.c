spl_recursive_it_rewind_ex(spl_recursive_it_object *object, zval *zthis TSRMLS_DC)
{
	zend_object_iterator      *sub_iter;

	if (!object->iterators) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "The %s instance wasn't initialized properly", Z_OBJCE_P(zthis)->name);
	}

	while (object->level) {
		sub_iter = object->iterators[object->level].iterator;
		sub_iter->funcs->dtor(sub_iter TSRMLS_CC);
		zval_ptr_dtor(&object->iterators[object->level--].zobject);
		if (!EG(exception) && (!object->endChildren || object->endChildren->common.scope != spl_ce_RecursiveIteratorIterator)) {
			zend_call_method_with_0_params(&zthis, object->ce, &object->endChildren, "endchildren", NULL);
		}
	}
	object->iterators = erealloc(object->iterators, sizeof(spl_sub_iterator));
	object->iterators[0].state = RS_START;
	sub_iter = object->iterators[0].iterator;
	if (sub_iter->funcs->rewind) {
		sub_iter->funcs->rewind(sub_iter TSRMLS_CC);
	}
	if (!EG(exception) && object->beginIteration && !object->in_iteration) {
		zend_call_method_with_0_params(&zthis, object->ce, &object->beginIteration, "beginIteration", NULL);
	}
	object->in_iteration = 1;
	spl_recursive_it_move_forward_ex(object, zthis TSRMLS_CC);
}
