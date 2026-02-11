free_parameter(Parameter * param)
{
    free_decl_spec(&param->decl_spec);
    free_declarator(param->declarator);
    if (param->comment != NULL)
	free(param->comment);
    free(param);
}
