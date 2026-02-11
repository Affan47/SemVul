free_declarator(Declarator * d)
{
    free(d->text);
    free(d->name);
    free_param_list(&d->params);
    if (d->func_stack != NULL)
	free_declarator(d->func_stack);
    free(d);
}
