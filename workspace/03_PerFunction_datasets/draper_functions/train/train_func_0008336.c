set_output_offset(section_offset_type output_offset,
		       unsigned int addralign,
		       Merge_map* merge_map)
{
  size_t length = this->contents_.length();


  length += 8;

  if (this->object_ != NULL)
    {

      merge_map->add_mapping(this->object_, this->shndx_, this->input_offset_,
			     length, output_offset);
    }

  length = align_address(length, addralign);

  for (std::vector<Fde*>::const_iterator p = this->fdes_.begin();
       p != this->fdes_.end();
       ++p)
    {
      (*p)->add_mapping(output_offset + length, merge_map);

      size_t fde_length = (*p)->length();
      fde_length = align_address(fde_length, addralign);
      length += fde_length;
    }

  return output_offset + length;
}
