set_verbosity(const char *component,int level)
{
    COMPONENT *walk;

    if (!component) {
	default_verbosity = level;
	return;
    }
    for (walk = components; walk; walk = walk->next)
	if (!strcmp(walk->name,component)) break;
    if (!walk) {
	walk = alloc_t(COMPONENT);
	walk->name = component;
	walk->next = components;
	components = walk;
    }
    walk->verbosity = level;
}
