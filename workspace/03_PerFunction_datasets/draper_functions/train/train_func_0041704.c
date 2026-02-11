_free_params(module_param_t *param)
{
    module_param_t *next;
    next = NULL;
    do
    {
        if (param->name) free(param->name);
        if (param->value) free(param->value);
        next = param->next;
        free(param);

        param = next;
    } while (next != NULL);
}
