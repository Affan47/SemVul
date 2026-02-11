list_add(void *ptr, void *data, size_t size)
{
	void *result = NULL;

	if (ptr && data && (size > 0)) {
		result = _new(data, size);
		if (result != NULL) {
			switch (_Type(ptr)) {
			case TYPE_LIST:
				_put_front(_List(ptr), result);
				break;
			case TYPE_NODE:
				_put_before(_Node(ptr), result);
				break;
			default:
				abort();
			}
		}
	}
	return result + sizeof(struct node);
}
