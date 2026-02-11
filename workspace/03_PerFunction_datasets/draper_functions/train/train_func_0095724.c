get_string(Stream *htio, classfile *clazz, uint index)
{
	return (index < clazz->cpool_count) ? clazz->cpool[index]->value.string : (char*)"?";
}
