readArray(FILE* file)
{
  if(file == 0) { return; }
  size_t* array_buffer = new size_t[this->block_size * this->number_of_blocks];
  if(!std::fread(array_buffer, this->block_size * sizeof(size_t), this->number_of_blocks, file)) { return; }
  this->array = array_buffer;
}
