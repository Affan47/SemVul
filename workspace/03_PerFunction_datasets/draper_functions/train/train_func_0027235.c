lab_var(lua_State *L)
{
  THTensor *t = luaT_checkudata(L, 1, torch_Tensor_id);
  int flag = luaT_optboolean(L, 2, 0);
  int dimension = luaL_optint(L, 3, 1)-1;
  THTensor *r = NULL;
  long *dim;
  int i;

  luaL_argcheck(L, dimension >= 0 && dimension < t->nDimension, 3, "invalid dimension");

  dim = THAlloc(sizeof(long)*t->nDimension);
  for(i = 0; i < t->nDimension; i++)
    dim[i] = t->size[i];
  dim[dimension] = 1;
  r = THTensor_newWithSize(t->nDimension, dim, NULL);
  luaT_pushudata(L, r, torch_Tensor_id);
  THFree(dim);

  TH_TENSOR_DIM_APPLY2(double, t, double, r, dimension,
                       double sum = 0;
                       double sum2 = 0;
                       long i;
                       for(i = 0; i < t_size; i++)
                       {
                         double z = t_p[i*t_stride];
                         sum += z;
                         sum2 += z*z;
                       }

                       if(flag)
                       {
                         sum /= t_size;
                         sum2 /= t_size;
                         sum2 -= sum*sum;
                         sum2 = (sum2 < 0 ? 0 : sum2);
                         *r_p = sum2;
                       }
                       else
                       {
                         sum /= t_size;
                         sum2 /= t_size-1;
                         sum2 -= ((double)t_size)/((double)(t_size-1))*sum*sum;
                         sum2 = (sum2 < 0 ? 0 : sum2);
                         *r_p = sum2;
                       })

  return 1;
}
