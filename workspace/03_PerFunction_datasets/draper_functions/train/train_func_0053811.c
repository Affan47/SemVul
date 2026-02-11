produce_asm (struct output_block *ob, tree fn)
{
  enum lto_section_type section_type = ob->section_type;
  struct lto_function_header header;
  char *section_name;
  struct lto_output_stream *header_stream;

  if (section_type == LTO_section_function_body)
    {
      const char *name = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (fn));
      section_name = lto_get_section_name (section_type, name, NULL);
    }
  else
    section_name = lto_get_section_name (section_type, NULL, NULL);

  lto_begin_section (section_name, !flag_wpa);
  free (section_name);


  memset (&header, 0, sizeof (struct lto_function_header));


  header.lto_header.major_version = LTO_major_version;
  header.lto_header.minor_version = LTO_minor_version;

  header.compressed_size = 0;

  if (section_type == LTO_section_function_body)
    header.cfg_size = ob->cfg_stream->total_size;
  header.main_size = ob->main_stream->total_size;
  header.string_size = ob->string_stream->total_size;

  header_stream = XCNEW (struct lto_output_stream);
  lto_output_data_stream (header_stream, &header, sizeof header);
  lto_write_stream (header_stream);
  free (header_stream);


  if (section_type == LTO_section_function_body)
    lto_write_stream (ob->cfg_stream);
  lto_write_stream (ob->main_stream);
  lto_write_stream (ob->string_stream);

  lto_end_section ();
}
