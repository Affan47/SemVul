delete_global_var(vm_globalvar_t *var)
{

    if (var->nxt != 0)
        var->nxt->prv = var->prv;

    if (var->prv != 0)
        var->prv->nxt = var->nxt;
    else
        global_var_head_ = var->nxt;


    delete var;
}
