push_replacement_text (cpp_reader *pfile, cpp_hashnode *node)
{
  size_t len;
  const uchar *text;
  uchar *buf;

  if (node->flags & NODE_BUILTIN)
    {
      text = _cpp_builtin_macro_text (pfile, node);
      len = ustrlen (text);
      buf = _cpp_unaligned_alloc (pfile, len + 1);
      memcpy (buf, text, len);
      buf[len]='\n';
      text = buf;
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
