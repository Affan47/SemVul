hir(exec_list *instructions,
                         struct _mesa_glsl_parse_state *state)
{
   YYLTYPE loc = this->get_location();


   if (state->gs_input_prim_type_specified &&
       state->gs_input_prim_type != this->prim_type) {
      _mesa_glsl_error(&loc, state,
                       "geometry shader input layout does not match"
                       " previous declaration");
      return NULL;
   }


   unsigned num_vertices = vertices_per_prim(this->prim_type);
   if (state->gs_input_size != 0 && state->gs_input_size != num_vertices) {
      _mesa_glsl_error(&loc, state,
                       "this geometry shader input layout implies %u vertices"
                       " per primitive, but a previous input is declared"
                       " with size %u", num_vertices, state->gs_input_size);
      return NULL;
   }

   state->gs_input_prim_type_specified = true;
   state->gs_input_prim_type = this->prim_type;


   foreach_list (node, instructions) {
      ir_variable *var = ((ir_instruction *) node)->as_variable();
      if (var == NULL || var->data.mode != ir_var_shader_in)
         continue;


      if (var->type->is_unsized_array()) {
         if (var->data.max_array_access >= num_vertices) {
            _mesa_glsl_error(&loc, state,
                             "this geometry shader input layout implies %u"
                             " vertices, but an access to element %u of input"
                             " `%s' already exists", num_vertices,
                             var->data.max_array_access, var->name);
         } else {
            var->type = glsl_type::get_array_instance(var->type->fields.array,
                                                      num_vertices);
         }
      }
   }

   return NULL;
}
