fosfat_read_data (fosfat_t *fosfat, uint32_t block,
                  uint8_t nbs, fosfat_type_t type)
{
  if (!fosfat)
    return NULL;

  switch (type)
  {
  case B_BL:
  {
    int i;
    fosfat_bl_t *block_list, *first_bl;

    first_bl = fosfat_read_bl (fosfat, block);
    if (!first_bl)
      break;

    block_list = first_bl;
    block_list->pt = block;

    for (i = 1; block_list && i < nbs; i++)
    {
      block_list->next_bl = fosfat_read_bl (fosfat, block + (uint32_t) i);
      block_list = block_list->next_bl;

      if (block_list)
        block_list->pt = block + (uint32_t) i;
    }
    return first_bl;
  }

  case B_DATA:
  {
    int i;
    fosfat_data_t *block_data, *first_data;

    first_data = fosfat_read_d (fosfat, block);
    if (!first_data)
      break;

    block_data = first_data;

    for (i = 1; block_data && i < nbs; i++)
    {
      block_data->next_data = fosfat_read_d (fosfat, block + (uint32_t) i);
      block_data = block_data->next_data;
    }
    return first_data;
  }

  default:
    break;
  }

  return NULL;
}
