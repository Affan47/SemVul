DXSetComponentValue(Field f, char *name, Object value)
{
    struct component *c;


    if (!value)
    {
	DXDeleteComponent(f, name);
	return f;
    }

    CHECK(f, CLASS_FIELD);


    c = look_component(f, name, value? 1: 0);
    if (!c)
	return NULL;


    if (value!=c->value) {
	DXReference(value);
	if (value && c->value)
	    DXCopyAttributes(value, c->value);
	DXDelete(c->value);
	c->value = value;
    }

    return f;
}
