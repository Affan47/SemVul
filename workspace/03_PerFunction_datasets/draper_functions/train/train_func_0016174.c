late_string(void *obj, attrsym_t * attr, char *def)
{
    if (!attr || !obj)
	return def;
    return agxget(obj, attr);
}
