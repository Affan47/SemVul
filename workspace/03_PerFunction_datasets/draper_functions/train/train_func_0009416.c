VarFindEnv(const char name[], GNode *ctxt)
{
	Var	*var;

	name = VarLocal(name);

	if ((var = VarLookup(&ctxt->context, name)) != NULL)
		return (var);

	if ((var = VarLookup(&VAR_ENV->context, name)) != NULL)
		return (var);

	return (NULL);
}
