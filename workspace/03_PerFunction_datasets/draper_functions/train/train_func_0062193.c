DF24putimage(const char *filename, const void * image, int32 xdim, int32 ydim)
{
  CONSTR(FUNC, "DF24putimage");
  intn ret_value = SUCCEED;


  if (!dimsset && DFGRIsetdims(xdim, ydim, 3, IMAGE) == FAIL)
    HGOTO_ERROR(DFE_BADDIM, FAIL);
  dimsset = 0;

  ret_value = (DFGRIaddimlut(filename, image, xdim, ydim, IMAGE, 0, 1));

done:
  if(ret_value == FAIL)
    {

    }


  return ret_value;
}
