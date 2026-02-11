note_eh_region_may_contain_throw (eh_region region)
{
  while (bitmap_set_bit (eh_region_may_contain_throw_map, region->index))
    {
      if (region->type == ERT_MUST_NOT_THROW)
	break;
      region = region->outer;
      if (region == NULL)
	break;
    }
}
