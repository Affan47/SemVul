finish_handler_sequence (tree try_block)
{
  RECHAIN_STMTS (try_block, TRY_HANDLERS (try_block));
  check_handlers (TRY_HANDLERS (try_block));
}
