nn_Max_forward(lua_State *L)
{
  THTensor *input = luaT_checkudata(L, 2, torch_Tensor_id);
  int dimension = luaT_getfieldcheckint(L, 1, "dimension")-1;
  THTensor *indices = luaT_getfieldcheckudata(L, 1, "indices", torch_Tensor_id);
  THTensor *output = luaT_getfieldcheckudata(L, 1, "output", torch_Tensor_id);

  long *dim;
  int i;

  luaL_argcheck(L, dimension >= 0 && dimension < input->nDimension, 2, "dimension out of range");

  dim = THAlloc(sizeof(long)*input->nDimension);
  for(i = 0; i < input->nDimension; i++)
    dim[i] = input->size[i];
  dim[dimension] = 1;
  THTensor_resize(output, input->nDimension, dim);
  THTensor_resize(indices, input->nDimension, dim);
  THFree(dim);

  TH_TENSOR_DIM_APPLY3(double, output, double, input, double, indices, dimension,
                       int theIndex = 0;
                       double theMax = input_p[0];
                       for(i = 1; i < input_size; i++)
                       {
                         if(input_p[i*input_stride] > theMax)
                         {
                           theIndex = i;
                           theMax = input_p[i*input_stride];
                         }
                       }
                       *indices_p = theIndex+1;
                       *output_p = theMax;)

  THTensor_select(output, NULL, dimension, 0);

  return 1;
}
