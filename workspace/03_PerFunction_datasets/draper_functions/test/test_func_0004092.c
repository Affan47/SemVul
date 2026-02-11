one_addr2line(Object* object,
                               unsigned int shndx, off_t offset,
                               size_t cache_size,
                               std::vector<std::string>* other_lines)
{
  Dwarf_line_info* lineinfo = NULL;
  std::vector<Addr2line_cache_entry>::iterator it;


  for (it = addr2line_cache.begin(); it != addr2line_cache.end(); ++it)
    {
      if (it->object == object && it->shndx == shndx)
        {
          lineinfo = it->dwarf_line_info;
          it->generation_count = next_generation_count;

          if (next_generation_count < (1U << 31))
            ++next_generation_count;

          if (it->access_count < 31)
            ++it->access_count;
          break;
        }
    }


  if (lineinfo == NULL)
  {
    switch (parameters->size_and_endianness())
      {
#ifdef HAVE_TARGET_32_LITTLE
        case Parameters::TARGET_32_LITTLE:
          lineinfo = new Sized_dwarf_line_info<32, false>(object, shndx); break;
#endif
#ifdef HAVE_TARGET_32_BIG
        case Parameters::TARGET_32_BIG:
          lineinfo = new Sized_dwarf_line_info<32, true>(object, shndx); break;
#endif
#ifdef HAVE_TARGET_64_LITTLE
        case Parameters::TARGET_64_LITTLE:
          lineinfo = new Sized_dwarf_line_info<64, false>(object, shndx); break;
#endif
#ifdef HAVE_TARGET_64_BIG
        case Parameters::TARGET_64_BIG:
          lineinfo = new Sized_dwarf_line_info<64, true>(object, shndx); break;
#endif
        default:
          gold_unreachable();
      }
    addr2line_cache.push_back(Addr2line_cache_entry(object, shndx, lineinfo));
  }


  std::string retval = lineinfo->addr2line(shndx, offset, other_lines);


  while (addr2line_cache.size() > cache_size)
    {
      unsigned int lowest_score = ~0U;
      std::vector<Addr2line_cache_entry>::iterator lowest
          = addr2line_cache.end();
      for (it = addr2line_cache.begin(); it != addr2line_cache.end(); ++it)
        {
          const unsigned int score = (it->generation_count
                                      + (1U << it->access_count));
          if (score < lowest_score)
            {
              lowest_score = score;
              lowest = it;
            }
        }
      if (lowest != addr2line_cache.end())
        {
          delete lowest->dwarf_line_info;
          addr2line_cache.erase(lowest);
        }
    }

  return retval;
}
