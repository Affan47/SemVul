debug_queue_symbol (tree decl)
{
  if (symbol_queue_index >= symbol_queue_size)
    {
      symbol_queue_size += 10;
      symbol_queue = XRESIZEVEC (tree, symbol_queue, symbol_queue_size);
    }

  symbol_queue[symbol_queue_index++] = decl;
}
