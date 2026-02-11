class_bind_struct(IrmoClass *klass, IrmoStruct *structure)
{
        IrmoClassVar *var;
        IrmoStructMember *member;
        unsigned int i;

        klass->structure = structure;


        for (i=0; i<klass->nvariables; ++i) {
                var = klass->variables[i];
                member = irmo_struct_get_member(structure, var->name);

                if (member != NULL) {
                        irmo_class_var_bind(var, member->name);
                }
        }
}
