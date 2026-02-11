e_list_iterator_set (EIterator *_iterator,
                     gconstpointer object)
{
	EListIterator *iterator = E_LIST_ITERATOR (_iterator);
	if (iterator->iterator) {
		if (iterator->list->free)
			iterator->list->free (iterator->iterator->data, iterator->list->closure);
		if (iterator->list->copy)
			iterator->iterator->data = iterator->list->copy (object, iterator->list->closure);
		else
			iterator->iterator->data = (gpointer) object;
	}
}
