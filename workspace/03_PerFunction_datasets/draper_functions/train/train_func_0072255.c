NC_free_dim(dim)
NC_dim *dim ;
{
    int ret_value = SUCCEED;

	if(dim != NULL)
      {
#ifdef HDF
          if (dim->count > 1)
            {
                dim->count -=  1;
                ret_value = SUCCEED;
                goto done;
            }
#endif

          if (NC_free_string(dim->name) == FAIL)
            {
                ret_value = FAIL;
                goto done;
            }
          Free(dim) ;
      }

done:
    if (ret_value == FAIL)
      {

      }


    return ret_value;
}
