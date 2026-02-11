calculate_head_size (const struct locarhead *h)
{
  off_t namehash_end = (h->namehash_offset
			+ h->namehash_size * sizeof (struct namehashent));
  off_t string_end =  h->string_offset + h->string_used;
  off_t locrectab_end = (h->locrectab_offset
			 + h->locrectab_used * sizeof (struct locrecent));
  return MAX (namehash_end, MAX (string_end, locrectab_end));
}
