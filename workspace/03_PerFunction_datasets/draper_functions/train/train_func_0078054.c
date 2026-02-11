text_action_add_literal (text_action_list *l,
			 text_action_t action,
			 const r_reloc *loc,
			 const literal_value *value,
			 int removed)
{
  text_action **m_p;
  text_action *ta;
  asection *sec = r_reloc_get_section (loc);
  bfd_vma offset = loc->target_offset;
  bfd_vma virtual_offset = loc->virtual_offset;

  BFD_ASSERT (action == ta_add_literal);

  for (m_p = &l->head; *m_p != NULL; m_p = &(*m_p)->next)
    {
      if ((*m_p)->offset > offset
	  && ((*m_p)->offset != offset
	      || (*m_p)->virtual_offset > virtual_offset))
	break;
    }


  ta = (text_action *) bfd_zmalloc (sizeof (text_action));
  ta->action = action;
  ta->sec = sec;
  ta->offset = offset;
  ta->virtual_offset = virtual_offset;
  ta->value = *value;
  ta->removed_bytes = removed;
  ta->next = (*m_p);
  *m_p = ta;
}
