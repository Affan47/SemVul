replaceDefinition(const char *name,
					const void *def, void **v)
{
	void *old_def = this->removeDefinition(name);
	if (v)
	    *v = old_def;
	this->addDefinition(name, def);
	return TRUE;
}
