parse_assertion (cpp_reader *pfile, struct answer **answerp, int type)
{
  cpp_hashnode *result = 0;
  const cpp_token *predicate;


  pfile->state.prevent_expansion++;

  *answerp = 0;
  predicate = cpp_get_token (pfile);
  if (predicate->type == CPP_EOF)
    cpp_error (pfile, CPP_DL_ERROR, "assertion without predicate");
  else if (predicate->type != CPP_NAME)
    cpp_error (pfile, CPP_DL_ERROR, "predicate must be an identifier");
  else if (parse_answer (pfile, answerp, type) == 0)
    {
      unsigned int len = NODE_LEN (predicate->val.node);
      unsigned char *sym = alloca (len + 1);


      sym[0] = '#';
      memcpy (sym + 1, NODE_NAME (predicate->val.node), len);
      result = cpp_lookup (pfile, sym, len + 1);
    }

  pfile->state.prevent_expansion--;
  return result;
}
