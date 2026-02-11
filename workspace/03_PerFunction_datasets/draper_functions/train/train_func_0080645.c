txs_type(const glsl_type *type)
{
   unsigned dims;
   switch (type->sampler_dimensionality) {
   case GLSL_SAMPLER_DIM_1D:
      dims = 1;
      break;
   case GLSL_SAMPLER_DIM_2D:
   case GLSL_SAMPLER_DIM_RECT:
   case GLSL_SAMPLER_DIM_CUBE:
      dims = 2;
      break;
   case GLSL_SAMPLER_DIM_3D:
      dims = 3;
      break;
   default:
      assert(!"Should not get here: invalid sampler dimensionality");
      dims = 2;
   }

   if (type->sampler_array)
      dims++;

   return glsl_type::get_instance(GLSL_TYPE_INT, dims, 1);
}
