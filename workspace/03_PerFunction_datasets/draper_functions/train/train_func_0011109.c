reliable_get_buf_output_sequenced (struct reliable *rel)
{
  struct gc_arena gc = gc_new ();
  int i;
  packet_id_type min_id = 0;
  bool min_id_defined = false;
  struct buffer *ret = NULL;


  for (i = 0; i < rel->size; ++i)
    {
      const struct reliable_entry *e = &rel->array[i];
      if (e->active)
	{
	  if (!min_id_defined || reliable_pid_min (e->packet_id, min_id))
	    {
	      min_id_defined = true;
	      min_id = e->packet_id;
	    }
	}
    }

  if (!min_id_defined || reliable_pid_in_range1 (rel->packet_id, min_id, rel->size))
    {
      ret = reliable_get_buf (rel);
    }
  else
    {
      dmsg (D_REL_LOW, "ACK output sequence broken: %s", reliable_print_ids (rel, &gc));
    }
  gc_free (&gc);
  return ret;
}
