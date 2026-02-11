getVariable(CState *st, char *name)
{
	Variable	key,
			   *var;


	if (st->nvariables <= 0)
		return NULL;

	key.name = name;
	var = (Variable *) bsearch((void *) &key,
							   (void *) st->variables,
							   st->nvariables,
							   sizeof(Variable),
							   compareVariables);
	if (var != NULL)
		return var->value;
	else
		return NULL;
}
