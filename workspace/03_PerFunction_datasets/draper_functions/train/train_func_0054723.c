random_r__ (struct UT_random_data *buf, UT_sint32 *result)
{
  UT_sint32 *state;

  if (buf == NULL || result == NULL)
    goto fail;

  state = buf->state;

  if (buf->rand_type == TYPE_0)
    {
      UT_sint32 val = state[0];
      val = ((state[0] * 1103515245) + 12345) & 0x7fffffff;
      state[0] = val;
      *result = val;
    }
  else
    {
      UT_sint32 *fptr = buf->fptr;
      UT_sint32 *rptr = buf->rptr;
      UT_sint32 *end_ptr = buf->end_ptr;
      UT_sint32 val;

      val = *fptr += *rptr;

      *result = (val >> 1) & 0x7fffffff;
      ++fptr;
      if (fptr >= end_ptr)
	{
	  fptr = state;
	  ++rptr;
	}
      else
	{
	  ++rptr;
	  if (rptr >= end_ptr)
	    rptr = state;
	}
      buf->fptr = fptr;
      buf->rptr = rptr;
    }
  return 0;

 fail:
  errno=EINVAL;
  return -1;
}
