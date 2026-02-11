free_line_layout(__this__)
{
  itk_hash_table* hash_table = PREPARED(this);
  if (hash_table)
    itk_free_hash_table(hash_table, true, false);
  free(GAP_(this));
  free(ALIGN_(this));
  free(this->data);
  free(this);
}
