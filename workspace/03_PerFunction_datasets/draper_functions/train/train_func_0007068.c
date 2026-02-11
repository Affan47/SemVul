arraylist_enlarge(ArrayList *arraylist)
{
	ArrayListValue *data;
	unsigned int newsize;


	newsize = arraylist->_alloced * 2;


	data = realloc(arraylist->data, sizeof(ArrayListValue) * newsize);

	if (data == NULL) {
		return 0;
	} else {
		arraylist->data = data;
		arraylist->_alloced = newsize;

		return 1;
	}
}
