resize(short new_count)
{
  assert(new_count >= 0);
  if (new_count == this->count) return;
  Data *new_data = (new_count > 0 ? new Data[new_count] : VXL_NULLPTR);

  if (this->count <= new_count) {
    short i = 0;
    if( this->data && new_data )
      {
      for (; i < this->count; i++)
        new_data[i] = this->data[i];
      }
    for (; i < new_count; i++)
      new_data[i] = 0;
  }
  else {
    for (short i = 0; i < new_count; i++)
      new_data[i] = this->data[i];
  }

  delete [] this->data;
  this->data = new_data;
  this->count = new_count;
}
