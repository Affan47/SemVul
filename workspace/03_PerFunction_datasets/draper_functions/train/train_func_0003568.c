lex_end(LEX *lex)
{
  DBUG_ENTER("lex_end");
  DBUG_PRINT("enter", ("lex: 0x%lx", (long) lex));


  if (lex->plugins.elements)
  {
    plugin_unlock_list(0, (plugin_ref*)lex->plugins.buffer,
                       lex->plugins.elements);
  }
  reset_dynamic(&lex->plugins);

  delete lex->sphead;
  lex->sphead= NULL;

  DBUG_VOID_RETURN;
}
