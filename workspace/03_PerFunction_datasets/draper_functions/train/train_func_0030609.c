envupd(char *name, Word *value)
{
	Envy *e;

	for(e = envy; e->name; e++)
		if(strcmp(name, e->name) == 0){
			delword(e->values);
			e->values = value;
			return;
		}
	e->name = name;
	e->values = value;
	envinsert(0,0);
}
