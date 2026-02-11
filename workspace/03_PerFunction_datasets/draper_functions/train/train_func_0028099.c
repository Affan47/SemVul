off()
{
	state(dead);
	int i;
	for(i = 0; i < MAX_BOLTS; i++)
		if(bolt_objects[i])
		{
			gengine->free_obj(bolt_objects[i]);
			bolt_objects[i] = NULL;
		}
}
