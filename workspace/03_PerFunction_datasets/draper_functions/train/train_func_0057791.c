infix_load_file_info(const char *filename)
{
  infix_file r;
  glsi32 c;
  int lines_allocated = 0;

  r.filename = filename;
  r.num_lines = 0;
  r.line_locations = NULL;

  r.stream = n_file_name(fileusage_Data | fileusage_TextMode,
			 filemode_Read, filename);

  if(!r.stream)
    return r;

  lines_allocated = 256;
  r.line_locations = (glui32 *) n_malloc(lines_allocated * sizeof(*r.line_locations));
  r.line_locations[r.num_lines] = 0;
  r.num_lines++;

  while((c = glk_get_char_stream(r.stream)) != GLK_EOF) {
    if(c == 10) {
      if(r.num_lines >= lines_allocated) {
	glui32 *new_locations;

	lines_allocated *= 2;
	new_locations = (glui32 *) n_realloc(r.line_locations,
				  lines_allocated * sizeof(*r.line_locations));
	r.line_locations = new_locations;
      }
      r.line_locations[r.num_lines] = glk_stream_get_position(r.stream);
      r.num_lines++;
    }
  }
  return r;
}
