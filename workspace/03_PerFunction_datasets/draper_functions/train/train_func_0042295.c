_dlerror_run (void (*operate) (void *), void *args)
{
  struct dl_action_result *result;


  __libc_once (once, init);


  if (static_buf != NULL)
    result = static_buf;
  else
    {


      result = __libc_getspecific (key);
      if (result == NULL)
	{
	  result = (struct dl_action_result *) calloc (1, sizeof (*result));
	  if (result == NULL)


	    result = &last_result;
	  else

	    __libc_setspecific (key, result);
	}
    }

  if (result->errstring != NULL)
    {


      if (result->malloced)
	free ((char *) result->errstring);
      result->errstring = NULL;
    }

  result->errcode = GLRO(dl_catch_error) (&result->objname, &result->errstring,
					  &result->malloced, operate, args);


  result->returned = result->errstring == NULL;

  return result->errstring != NULL;
}
