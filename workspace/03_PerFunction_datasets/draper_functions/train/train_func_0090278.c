find_or_add(uint64_t signature,
					unsigned int* slotp)
{
  if (this->capacity_ == 0)
    this->initialize();
  unsigned int slot =
      static_cast<unsigned int>(signature) & (this->capacity_ - 1);
  unsigned int secondary_hash;
  uint64_t probe = this->hash_table_[slot];
  if (probe != 0 && probe != signature)
    {
      secondary_hash = (static_cast<unsigned int>(signature >> 32)
			& (this->capacity_ - 1)) | 1;
      do
	{
	  slot = (slot + secondary_hash) & (this->capacity_ - 1);
	  probe = this->hash_table_[slot];
	} while (probe != 0 && probe != signature);
    }
  *slotp = slot;
  return (probe != 0);
}
