recursive_macro (cpp_reader *pfile, cpp_hashnode *node)
{
  bool recursing = !!(node->flags & NODE_DISABLED);


  if (recursing && node->value.macro->fun_like)
    {
      size_t depth = 0;
      cpp_context *context = pfile->context;

      do
	{
	  depth++;
	  if (context->macro == node && depth > 20)
	    break;
	  context = context->prev;
	}
      while (context);
      recursing = context != NULL;
    }

  if (recursing)
    cpp_error (pfile, CPP_DL_ERROR,
	       "detected recursion whilst expanding macro \"%s\"",
	       NODE_NAME (node));

  return recursing;
}
