irmo_class_new_variable(IrmoClass *klass,
                                      char *var_name,
                                      IrmoValueType var_type)
{
        IrmoClassVar *class_var;

        irmo_return_val_if_fail(klass != NULL, NULL);
        irmo_return_val_if_fail(var_name != NULL, NULL);
        irmo_return_val_if_fail(var_type != IRMO_TYPE_UNKNOWN
                             && var_type != IRMO_NUM_TYPES, NULL);

        if (klass->nvariables >= MAX_VARIABLES) {
                irmo_error_report("irmo_class_new_variable",
                                  "Maximum of %i variables per class",
                                  MAX_VARIABLES);
                return NULL;
        }

        if (irmo_hash_table_lookup(klass->variable_hash, var_name) != NULL) {
                irmo_error_report("irmo_class_new_variable",
                                  "Variable named '%s' already declared "
                                  "in class '%s'",
                                  var_name, klass->name);
                return NULL;
        }


        class_var = irmo_new0(IrmoClassVar, 1);

        class_var->name = strdup(var_name);
        class_var->type = var_type;
        class_var->index = klass->nvariables;
        class_var->klass = klass;


        klass->variables = irmo_renew(IrmoClassVar *, klass->variables,
                                      klass->nvariables + 1);
        klass->variables[klass->nvariables] = class_var;
        ++klass->nvariables;

        irmo_alloc_assert(irmo_hash_table_insert(klass->variable_hash,
                                                 class_var->name,
                                                 class_var));

        return class_var;
}
