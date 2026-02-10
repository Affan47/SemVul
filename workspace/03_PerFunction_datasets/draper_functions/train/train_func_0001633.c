getvarval(Var *var)
{
    return (var && (var->flags & VARSET)) ? &var->val : NULL;
}
