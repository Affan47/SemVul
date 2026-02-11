nn_Sum_backward(lua_State *L)
{
  THTensor *input = luaT_checkudata(L, 2, torch_Tensor_id);
  THTensor *gradOutput = luaT_checkudata(L, 3, torch_Tensor_id);
  int dimension = luaT_getfieldcheckint(L, 1, "dimension")-1;
  THTensor *gradInput = luaT_getfieldcheckudata(L, 1, "gradInput", torch_Tensor_id);

  long *dim, *str;
  int i, j;

  THTensor_resizeAs(gradInput, gradOutput);
  THTensor_copy(gradInput, gradOutput);

  dim = THAlloc(sizeof(long)*(gradOutput->nDimension+1));
  str = THAlloc(sizeof(long)*(gradOutput->nDimension+1));
  for(i = 0, j =  0; j < gradOutput->nDimension+1; j++)
  {
    if(j == dimension)
    {
      dim[j] = input->size[dimension];
      str[j] = 0;
      continue;
    }

    dim[j] = gradOutput->size[i];
    str[j] = gradOutput->stride[i];
    i++;
  }
  THTensor_setStorage(gradInput, gradInput->storage, gradInput->storageOffset, gradInput->nDimension+1, dim, str);
  THFree(dim);
  THFree(str);

  return 1;
}
