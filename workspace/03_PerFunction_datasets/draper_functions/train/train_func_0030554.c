add_variable(exec_list *instructions, glsl_symbol_table *symtab,
	     const char *name, const glsl_type *type,
	     enum ir_variable_mode mode, int slot)
{
   ir_variable *var = new(symtab) ir_variable(type, name, mode, glsl_precision_undefined);

   switch (var->mode) {
   case ir_var_auto:
   case ir_var_in:
   case ir_var_const_in:
   case ir_var_uniform:
   case ir_var_system_value:
      var->read_only = true;
      break;
   case ir_var_inout:
   case ir_var_out:
      break;
   default:
      assert(0);
      break;
   }

   var->location = slot;
   var->explicit_location = (slot >= 0);


   instructions->push_tail(var);

   symtab->add_variable(var);
   return var;
}
