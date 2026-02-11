indexForSelect()
{
  delete this->select_index;

  size_t index_samples = (this->number_of_blocks + BitVectorBase::INDEX_RATE - 1) / BitVectorBase::INDEX_RATE;
  this->select_rate = (this->items + index_samples - 1) / index_samples;
  index_samples = (this->items + this->select_rate - 1) / this->select_rate + 1;
  WriteBuffer index_buffer(index_samples, length(this->number_of_blocks - 1));


  size_t current = 0, pointer = 0;
  this->samples->goToItem(2);
  while(this->samples->hasNextItem())
  {
    size_t limit = this->samples->readItem();
    this->samples->skipItem();
    while(current < limit)
    {
      index_buffer.writeItem(pointer);
      current += this->select_rate;
    }
    pointer++;
  }
  index_buffer.writeItem(this->number_of_blocks - 1);

  this->select_index = index_buffer.getReadBuffer();
}
