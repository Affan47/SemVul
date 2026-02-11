bitwise_assign_unpack(ir_rvalue *lhs,
                                                     ir_rvalue *rhs)
{
   if (lhs->type->base_type != rhs->type->base_type) {


      assert(rhs->type->base_type == GLSL_TYPE_INT);
      switch (lhs->type->base_type) {
      case GLSL_TYPE_UINT:
         rhs = new(this->mem_ctx)
            ir_expression(ir_unop_i2u, lhs->type, rhs);
         break;
      case GLSL_TYPE_FLOAT:
         rhs = new(this->mem_ctx)
            ir_expression(ir_unop_bitcast_i2f, lhs->type, rhs);
         break;
      default:
         assert(!"Unexpected type conversion while lowering varyings");
         break;
      }
   }
   return new(this->mem_ctx) ir_assignment(lhs, rhs);
}
