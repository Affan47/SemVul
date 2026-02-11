gt_pch_note_object (void *obj, void *note_ptr_cookie,
		    gt_note_pointers note_ptr_fn)
{
  struct ptr_data **slot;

  if (obj == NULL || obj == (void *) 1)
    return 0;

  slot = (struct ptr_data **)
    htab_find_slot_with_hash (saving_htab, obj, POINTER_HASH (obj),
			      INSERT);
  if (*slot != NULL)
    {
      if ((*slot)->note_ptr_fn != note_ptr_fn
	  || (*slot)->note_ptr_cookie != note_ptr_cookie)
	abort ();
      return 0;
    }

  *slot = xcalloc (sizeof (struct ptr_data), 1);
  (*slot)->obj = obj;
  (*slot)->note_ptr_fn = note_ptr_fn;
  (*slot)->note_ptr_cookie = note_ptr_cookie;
  if (note_ptr_fn == gt_pch_p_S)
    (*slot)->size = strlen (obj) + 1;
  else
    (*slot)->size = ggc_get_size (obj);
  return 1;
}
