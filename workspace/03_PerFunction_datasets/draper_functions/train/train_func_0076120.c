push_replacement_text (pfile, node)
     cpp_reader *pfile;
     cpp_hashnode *node;
{
  size_t len;
  const uchar *text;

  if (node->flags & NODE_BUILTIN)
    {
      text = _cpp_builtin_macro_text (pfile, node);
      len = ustrlen (text);
    }
  else
    {
      cpp_macro *macro = node->value.macro;
      macro->used = 1;
      text = macro->exp.text;
      len = macro->count;
    }

  _cpp_push_text_context (pfile, node, text, len);
}
