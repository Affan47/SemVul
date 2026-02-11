cbf_make_handle (cbf_handle *handle)
{
  int errorcode;

  cbf_failnez (cbf_alloc ((void **) handle, NULL,
               sizeof (cbf_handle_struct), 1))

  errorcode = cbf_make_node (&(*handle)->node, CBF_ROOT, NULL, NULL);


  if (errorcode)

    return errorcode | cbf_free ((void **) handle, NULL);

  (*handle)->row = 0;

  (*handle)->search_row = 0;

  (*handle)->refcount = 1;

  (*handle)->dictionary = NULL;

  (*handle)->file = NULL;

  (*handle)->commentfile = NULL;

  (*handle)->logfile = stderr;

  (*handle)->warnings = 0;

  (*handle)->errors = 0;

  (*handle)->startline = 0;

  (*handle)->startcolumn = 0;

  return 0;
}
