update_forwarder_flag (basic_block bb)
{
  if (forwarder_block_p (bb))
    bb->flags |= BB_FORWARDER_BLOCK;
  else
    bb->flags &= ~BB_FORWARDER_BLOCK;
}
