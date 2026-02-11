copy_masked_offset(ir_constant *src, int offset, unsigned int mask)
{
   assert (!type->is_array() && !type->is_record());

   if (!type->is_vector() && !type->is_matrix()) {
      offset = 0;
      mask = 1;
   }

   int id = 0;
   for (int i=0; i<4; i++) {
      if (mask & (1 << i)) {
	 switch (this->type->base_type) {
	 case GLSL_TYPE_UINT:
	    value.u[i+offset] = src->get_uint_component(id++);
	    break;
	 case GLSL_TYPE_INT:
	    value.i[i+offset] = src->get_int_component(id++);
	    break;
	 case GLSL_TYPE_FLOAT:
	    value.f[i+offset] = src->get_float_component(id++);
	    break;
	 case GLSL_TYPE_BOOL:
	    value.b[i+offset] = src->get_bool_component(id++);
	    break;
	 default:
	    assert(!"Should not get here.");
	    return;
	 }
      }
   }
}
