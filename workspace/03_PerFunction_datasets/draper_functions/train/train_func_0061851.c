GB_LoadComponent(const char *name)
{
	CATCH_ERROR
	{
		COMPONENT *comp = COMPONENT_create(name);
		COMPONENT_load(comp);
	}
	END_CATCH_ERROR
}
