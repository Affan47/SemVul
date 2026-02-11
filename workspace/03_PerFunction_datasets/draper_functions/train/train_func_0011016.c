GB_GetClass(void *object)
{
	if (object)
		return OBJECT_class(object);
	else
		return EXEC.class;
}
