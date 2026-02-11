new_parameter(DeclSpec * decl_spec, Declarator * declarator)
{
    Parameter *param;
    param = NEW(Parameter);

    if (decl_spec == NULL) {
	new_decl_spec(&param->decl_spec, "", 0L, DS_NONE);
    } else {
	param->decl_spec = *decl_spec;
    }

    if (declarator == NULL) {
	declarator = new_declarator("", "", 0L);
    }
    param->declarator = declarator;

    param->comment = NULL;
    return param;
}
