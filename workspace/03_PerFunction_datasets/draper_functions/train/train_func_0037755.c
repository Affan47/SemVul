read_function(s_expression *expr, bool skip_body)
{
   bool added = false;
   s_symbol *name;

   s_pattern pat[] = { "function", name };
   if (!PARTIAL_MATCH(expr, pat)) {
      ir_read_error(expr, "Expected (function <name> (signature ...) ...)");
      return NULL;
   }

   ir_function *f = state->symbols->get_function(name->value());
   if (f == NULL) {
      f = new(mem_ctx) ir_function(name->value());
      added = state->symbols->add_function(f);
      assert(added);
   }

   exec_list_iterator it = ((s_list *) expr)->subexpressions.iterator();
   it.next();
   it.next();
   for (; it.has_next(); it.next()) {
      s_expression *s_sig = (s_expression *) it.get();
      read_function_sig(f, s_sig, skip_body);
   }
   return added ? f : NULL;
}
