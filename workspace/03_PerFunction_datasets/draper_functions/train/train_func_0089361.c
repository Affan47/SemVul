itk_new_hash_table_fine_tuned(long initial_capacity, float load_factor)
{
  itk_hash_table* this = calloc(1, sizeof(itk_hash_table));
  this->capacity = initial_capacity ? initial_capacity : 1;
  this->buckets = calloc(this->capacity, sizeof(itk_hash_entry*));
  this->load_factor = load_factor;
  this->threshold = (long)(this->capacity * load_factor);
  return this;
}
