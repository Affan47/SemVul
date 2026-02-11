get_current_attrib(texenv_fragment_program *p, GLuint attrib)
{
   ir_variable *current;
   ir_rvalue *val;

   current = p->shader->symbols->get_variable("gl_CurrentAttribFragMESA");
   assert(current);
   current->data.max_array_access = MAX2(current->data.max_array_access, attrib);
   val = new(p->mem_ctx) ir_dereference_variable(current);
   ir_rvalue *index = new(p->mem_ctx) ir_constant(attrib);
   return new(p->mem_ctx) ir_dereference_array(val, index);
}
