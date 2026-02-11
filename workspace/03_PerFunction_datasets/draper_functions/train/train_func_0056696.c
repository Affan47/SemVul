compute_packing_order(ir_variable *var)
{
   const glsl_type *element_type = var->type;

   while (element_type->base_type == GLSL_TYPE_ARRAY) {
      element_type = element_type->fields.array;
   }

   switch (element_type->component_slots() % 4) {
   case 1: return PACKING_ORDER_SCALAR;
   case 2: return PACKING_ORDER_VEC2;
   case 3: return PACKING_ORDER_VEC3;
   case 0: return PACKING_ORDER_VEC4;
   default:
      assert(!"Unexpected value of vector_elements");
      return PACKING_ORDER_VEC4;
   }
}
