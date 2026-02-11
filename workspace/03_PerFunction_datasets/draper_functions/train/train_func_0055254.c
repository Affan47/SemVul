set_name(const char *name)
{
	Assert(name != NULL);
	strcpy_s(this->m_name, name);
}
