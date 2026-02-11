free_iobject_proto(void *key, void *value, void *chat_type)
{
	if ((GPOINTER_TO_INT(key) >> 16) == GPOINTER_TO_INT(chat_type)) {
                free_iobject_hash(key, value);
                return TRUE;
	}

	return FALSE;
}
