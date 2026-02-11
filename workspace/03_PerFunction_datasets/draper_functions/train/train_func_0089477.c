alloc_section (guint8 *data, SectionType section_id, guint32 offset)
{
  int i;
  Header *header = (Header*)data;
  Section *section_data = (Section*)&data[header->sections];

  g_assert (section_id != GI_SECTION_END);

  for (i = 0; i < NUM_SECTIONS; i++)
    {
      if (section_data->id == GI_SECTION_END)
	{
	  section_data->id = section_id;
	  section_data->offset = offset;
	  return;
	}
      section_data++;
    }
  g_assert_not_reached ();
}
