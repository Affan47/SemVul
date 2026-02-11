lab_cumsum(lua_State *L)
{
  THTensor *t = luaT_checkudata(L, 1, torch_Tensor_id);
  int dimension = luaL_optint(L, 2, 1)-1;
  THTensor *r = NULL;
  long *dim;
  int i;

  luaL_argcheck(L,dimension >= 0 && dimension < t->nDimension, 2, "dimension out of range");

  dim = THAlloc(sizeof(long)*t->nDimension);
  for(i = 0; i < t->nDimension; i++)
    dim[i] = t->size[i];
  r = THTensor_newWithSize(t->nDimension, dim, NULL);
  THFree(dim);

  TH_TENSOR_DIM_APPLY2(double, t, double, r, dimension,
                       double cumsum = 0;
                       long i;
                       for(i = 0; i < t_size; i++)
                       {
                         cumsum += t_p[i*t_stride];
                         r_p[i*r_stride] = cumsum;
                       })

  luaT_pushudata(L, r, torch_Tensor_id);
  return 1;
}
