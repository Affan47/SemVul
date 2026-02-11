new_line (BusDesktopFileParser *parser)
{
  BusDesktopFileSection *section;
  BusDesktopFileLine *line;

  section = &parser->desktop_file->sections[parser->current_section];

  if (section->n_allocated_lines == section->n_lines)
    {
      if (!grow_lines_in_section (section))
        return NULL;
    }

  line = &section->lines[section->n_lines++];

  _DBUS_ZERO(*line);

  return line;
}
