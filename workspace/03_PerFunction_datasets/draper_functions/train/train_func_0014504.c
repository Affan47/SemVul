ea_kill_text (int from, int to)
{
  register int i, counter, distance;
  int killing_backwards, slot;
  char *killed_text;

  killing_backwards = (from > to);


  if (killing_backwards)
    {
      int temp = from;
      from = to;
      to = temp;
    }


  distance = to - from;
  killed_text = xmalloc (1 + distance);
  strncpy (killed_text, &input_line[from], distance);
  killed_text[distance] = '\0';


  counter = input_line_end - to;

  for (i = from; counter; i++, counter--)
    input_line[i] = input_line[i + distance];

  input_line_end -= distance;


  if (echo_area_last_command_was_kill)
    {
      char *old, *new;

      slot = kill_ring_loc;
      old = kill_ring[slot];
      new = xmalloc (1 + strlen (old) + strlen (killed_text));

      if (killing_backwards)
        {

          strcpy (new, killed_text);
          strcat (new, old);
        }
      else
        {

          strcpy (new, old);
          strcat (new, killed_text);
        }

      free (old);
      free (killed_text);
      kill_ring[slot] = new;
    }
  else
    {


      slot = kill_ring_index;

      if (slot == max_retained_kills)
        slot = 0;

      if (slot + 1 > kill_ring_slots)
        kill_ring = xrealloc (kill_ring,
			      (kill_ring_slots += max_retained_kills)
			      * sizeof (char *));

      if (slot != kill_ring_index)
        free (kill_ring[slot]);
      else
        kill_ring_index++;

      kill_ring[slot] = killed_text;

      kill_ring_loc = slot;
    }


  echo_area_last_command_was_kill++;
}
