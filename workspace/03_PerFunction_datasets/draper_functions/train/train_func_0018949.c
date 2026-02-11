deallocate(char* ptr, int power, size_t )
{
  ptr -= sizeof(BlockNode*);
  BlockNode* block = *reinterpret_cast<BlockNode**>(ptr);
  Node* chunk = reinterpret_cast<Node*>(ptr);
  if (block->M_chunks.empty())
  {

    block->unlink();
    M_list_notfull[power - minimum_size_exp].insert_back(block);
  }
  block->M_chunks.insert(chunk);
  if (--block->M_chunks.M_used_count == 0 && M_count[power - minimum_size_exp] > M_keep[power - minimum_size_exp])
  {

    block->unlink();
    ::operator delete(block);
    --M_count[power - minimum_size_exp];
  }
}
