is_basis() const
{
   if (!this->type->is_scalar() && !this->type->is_vector())
      return false;

   if (this->type->is_boolean())
      return false;

   unsigned ones = 0;
   for (unsigned c = 0; c < this->type->vector_elements; c++) {
      switch (this->type->base_type) {
      case GLSL_TYPE_FLOAT:
	 if (this->value.f[c] == 1.0)
	    ones++;
	 else if (this->value.f[c] != 0.0)
	    return false;
	 break;
      case GLSL_TYPE_INT:
	 if (this->value.i[c] == 1)
	    ones++;
	 else if (this->value.i[c] != 0)
	    return false;
	 break;
      case GLSL_TYPE_UINT:
	 if (int(this->value.u[c]) == 1)
	    ones++;
	 else if (int(this->value.u[c]) != 0)
	    return false;
	 break;
      default:


	 assert(!"Should not get here.");
	 return false;
      }
   }

   return ones == 1;
}
