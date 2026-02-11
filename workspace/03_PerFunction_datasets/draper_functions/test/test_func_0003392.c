obj_elf_version (int ignore ATTRIBUTE_UNUSED)
{
  char *name;
  unsigned int c;
  char *p;
  asection *seg = now_seg;
  subsegT subseg = now_subseg;
  Elf_Internal_Note i_note;
  Elf_External_Note e_note;
  asection *note_secp = NULL;

  SKIP_WHITESPACE ();
  if (*input_line_pointer == '\"')
    {
      unsigned int len;

      ++input_line_pointer;
      name = input_line_pointer;

      while (is_a_char (c = next_char_of_string ()))
	;
      c = *input_line_pointer;
      *input_line_pointer = '\0';
      *(input_line_pointer - 1) = '\0';
      *input_line_pointer = c;


      note_secp = subseg_new (".note", 0);
      bfd_set_section_flags (stdoutput,
			     note_secp,
			     SEC_HAS_CONTENTS | SEC_READONLY);


      len = strlen (name) + 1;


      i_note.namesz = len;
      i_note.descsz = 0;
      i_note.type = NT_VERSION;
      p = frag_more (sizeof (e_note.namesz));
      md_number_to_chars (p, i_note.namesz, sizeof (e_note.namesz));
      p = frag_more (sizeof (e_note.descsz));
      md_number_to_chars (p, i_note.descsz, sizeof (e_note.descsz));
      p = frag_more (sizeof (e_note.type));
      md_number_to_chars (p, i_note.type, sizeof (e_note.type));
      p = frag_more (len);
      memcpy (p, name, len);

      frag_align (2, 0, 0);

      subseg_set (seg, subseg);
    }
  else
    as_bad (_("expected quoted string"));

  demand_empty_rest_of_line ();
}
