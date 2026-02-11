writeArray(FILE* file) const
{
  if(file == 0) { return; }
  std::fwrite(this->array, this->block_size * sizeof(size_t), this->number_of_blocks, file);
}
