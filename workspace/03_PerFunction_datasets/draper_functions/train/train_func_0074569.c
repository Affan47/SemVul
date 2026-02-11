get_module_ae_list(Module_table *module)
{
    int oldentry = get_module_entry_before_d2a(module);

    if (oldentry == 0) {
        return NULL;
    } else if (module->kind == MODULE_FUNC) {
        return dva.func_arg[oldentry];
    } else if (module->kind == MODULE_SUB) {
        return dva.subr_arg[oldentry];
    } else {
        return NULL;
    }
}
