DefineEntity(Dtd dtd, Entity e, int pe)
{
    if(pe)
    {
	e->next = dtd->parameter_entities;
	dtd->parameter_entities = e;
    }
    else
    {
	e->next = dtd->entities;
	dtd->entities = e;
    }

    return e;
}
