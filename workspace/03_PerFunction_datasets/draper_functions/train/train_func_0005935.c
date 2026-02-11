indexForRank()
{
  delete this->rank_index;

  size_t value_samples = (this->number_of_blocks + BitVectorBase::INDEX_RATE - 1) / BitVectorBase::INDEX_RATE;
  this->rank_rate = (this->size + value_samples - 1) / value_samples;
  value_samples = (this->size + this->rank_rate - 1) / this->rank_rate + 1;
  WriteBuffer index_buffer(value_samples, length(this->number_of_blocks - 1));


  size_t current = 0, pointer = 0;
  this->samples->goToItem(2);
  while(this->samples->hasNextItem())
  {
    this->samples->skipItem();
    size_t limit = this->samples->readItem();
    while(current < limit)
    {
      index_buffer.writeItem(pointer);
      current += this->rank_rate;
    }
    pointer++;
  }
  index_buffer.writeItem(this->number_of_blocks - 1);

  this->rank_index = index_buffer.getReadBuffer();
}
