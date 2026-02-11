set_memory_constraints(void)
{
  if (!decompress) {
    total_in_slots = 2u * num_worker;
    total_out_slots = 2u * num_worker + 2;
    in_granul = bs100k * 100000u;
    out_granul = -1;
  }
  else if (!small) {
    total_in_slots = 4u * num_worker;
    total_out_slots = 16u * num_worker;
    in_granul = 256u * 1024u;
    out_granul = MAX_BLOCK_SIZE;
  }
  else {
    total_in_slots = 2u;
    total_out_slots = 2u * num_worker;
    in_granul = 32768u;
    out_granul = 900000u;
  }
}
