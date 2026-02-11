add_block(BasicBlock* block) {
  block->index = counter;
  counter++;

  block->add_op(new CFG_Phis(block));

  blocks.push_back(block);

  if (blocks.size() == 1)
    working_block = block;
}
