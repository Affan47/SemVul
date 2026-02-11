read_emit_vertex(s_expression *expr)
{
   s_pattern pat[] = { "emit-vertex" };

   if (MATCH(expr, pat)) {
      return new(mem_ctx) ir_emit_vertex();
   }
   ir_read_error(NULL, "when reading emit-vertex");
   return NULL;
}
