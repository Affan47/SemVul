mark(struct gl_program *prog, ir_variable *var, int offset, int len,
     bool is_fragment_shader)
{


   for (int i = 0; i < len; i++) {
      GLbitfield64 bitfield =
         BITFIELD64_BIT(var->data.location + var->data.index + offset + i);
      if (var->data.mode == ir_var_shader_in) {
	 prog->InputsRead |= bitfield;
         if (is_fragment_shader) {
            gl_fragment_program *fprog = (gl_fragment_program *) prog;
            fprog->InterpQualifier[var->data.location +
                                   var->data.index + offset + i] =
               (glsl_interp_qualifier) var->data.interpolation;
            if (var->data.centroid)
               fprog->IsCentroid |= bitfield;
            if (var->data.sample)
               fprog->IsSample |= bitfield;
         }
      } else if (var->data.mode == ir_var_system_value) {
         prog->SystemValuesRead |= bitfield;
      } else {
         assert(var->data.mode == ir_var_shader_out);
	 prog->OutputsWritten |= bitfield;
      }
   }
}
