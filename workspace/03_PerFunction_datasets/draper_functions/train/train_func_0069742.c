constant_referenced(struct hash_table *variable_context,
					     ir_constant *&store, int &offset) const
{
   if (variable_context) {
      store = (ir_constant *)hash_table_find(variable_context, var);
      offset = 0;
   } else {
      store = NULL;
      offset = 0;
   }
}
