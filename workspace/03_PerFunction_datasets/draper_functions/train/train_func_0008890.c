Levels_reset(Levels *self)
{
	int i;
	self->currentLevel = 1;

	for (i = 0; i < IO_OP_MAX_LEVEL; i ++)
	{
		Level *level = &self->pool[i];
		level->type = UNUSED;
	}

	{
		Level *level = &self->pool[0];
		level->message = NULL;
		level->type = NEW;
		level->precedence = IO_OP_MAX_LEVEL;
	}

	List_removeAll(self->stack);
	List_append_(self->stack, &self->pool[0]);
}
