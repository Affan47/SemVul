coerce(Table *table, Symbol *var, Type val_type)
{
    Type var_type = gettype(table, var);

    if (isint(var_type))
    {
        if (isfloat(val_type))
            emit(f2i);

    }
    else if (isfloat(var_type))
    {
        if (isint(val_type))
            emit(i2f);
    }
    else if (isstr(var_type))
    {
        if (isstr(val_type))
        {}
        else
        {
            printf("var_type %s", var_type);
            printf("val_type %s", val_type);
            error("Type error sds");

        }
    }
    else
    {
        printf("var_type %s", var_type);
        error("Type error sd");
    }
}
