new_hash()
{
  HASH this;
  int  size = 10240;

  this = calloc(sizeof(*this),1);
  this->size    = size;
  this->entries = 0;
  this->index   = 0;
  while (this->size < size) {
    this->size <<= 1;
  }
  this->table = (NODE**)calloc(this->size * sizeof(NODE*), 1);
  return this;
}
