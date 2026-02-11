start_cleanup_deferral ()
{


  if (block_stack)
    ++block_stack->data.block.conditional_code;
}
