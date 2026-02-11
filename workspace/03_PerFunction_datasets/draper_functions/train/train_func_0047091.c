rsrc_write_entry (rsrc_write_data *  data,
		  bfd_byte *         where,
		  rsrc_entry *       entry)
{
  if (entry->is_name)
    {
      bfd_put_32 (data->abfd,
		  SetHighBit (data->next_string - data->datastart),
		  where);
      rsrc_write_string (data, & entry->name_id.name);
    }
  else
    bfd_put_32 (data->abfd, entry->name_id.id, where);

  if (entry->is_dir)
    {
      bfd_put_32 (data->abfd,
		  SetHighBit (data->next_table - data->datastart),
		  where + 4);
      rsrc_write_directory (data, entry->value.directory);
    }
  else
    {
      bfd_put_32 (data->abfd, data->next_leaf - data->datastart, where + 4);
      rsrc_write_leaf (data, entry->value.leaf);
    }
}
