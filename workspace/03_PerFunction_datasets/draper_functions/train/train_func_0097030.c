query_variable(char *varname)

{   struct vardefn *var;

    for (var=vardefns; var!=NULL; var=var->next) {
        if (strcmp(varname, var->varname) == 0) return var->value;
    }

    return NULL;
}
