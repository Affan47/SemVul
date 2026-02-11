sort_line_sequences (struct line_info_table* table)
{
  bfd_size_type amt;
  struct line_sequence* sequences;
  struct line_sequence* seq;
  unsigned int n = 0;
  unsigned int num_sequences = table->num_sequences;
  bfd_vma last_high_pc;

  if (num_sequences == 0)
    return TRUE;


  amt = sizeof (struct line_sequence) * num_sequences;
  sequences = (struct line_sequence *) bfd_alloc (table->abfd, amt);
  if (sequences == NULL)
    return FALSE;


  seq = table->sequences;
  for (n = 0; n < num_sequences; n++)
    {
      struct line_sequence* last_seq = seq;

      BFD_ASSERT (seq);
      sequences[n].low_pc = seq->low_pc;
      sequences[n].prev_sequence = NULL;
      sequences[n].last_line = seq->last_line;
      seq = seq->prev_sequence;
      free (last_seq);
    }
  BFD_ASSERT (seq == NULL);

  qsort (sequences, n, sizeof (struct line_sequence), compare_sequences);


  num_sequences = 1;
  last_high_pc = sequences[0].last_line->address;
  for (n = 1; n < table->num_sequences; n++)
    {
      if (sequences[n].low_pc < last_high_pc)
        {
	  if (sequences[n].last_line->address <= last_high_pc)

	    continue;


	  sequences[n].low_pc = last_high_pc;
        }
      last_high_pc = sequences[n].last_line->address;
      if (n > num_sequences)
        {

          sequences[num_sequences].low_pc = sequences[n].low_pc;
          sequences[num_sequences].last_line = sequences[n].last_line;
        }
      num_sequences++;
    }

  table->sequences = sequences;
  table->num_sequences = num_sequences;
  return TRUE;
}
