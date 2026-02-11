parse_insn_templ (const char *s, insn_templ *t)
{
  const char *p = s;
  int insn_name_len;
  split_rec oprec;
  int i;


  init_split_rec (&oprec);

  p = skip_white (p);
  insn_name_len = strcspn (s, " ");
  if (insn_name_len == 0)
    return FALSE;

  init_insn_templ (t);
  t->opcode_name = enter_opname_n (p, insn_name_len);

  p = p + insn_name_len;


  split_string (&oprec, p, ',', TRUE);

  for (i = 0; i < oprec.count; i++)
    {
      const char *opname = oprec.vec[i];
      opname_map_e *e = (opname_map_e *) xmalloc (sizeof (opname_map_e));
      e->next = NULL;
      e->operand_name = NULL;
      e->constant_value = 0;
      e->operand_num = i;


      if (opname && opname[0] >= '0' && opname[0] <= '9')
	{
	  unsigned val;

	  if (parse_constant (opname, &val))
	    e->constant_value = val;
	  else
	    {
	      free (e);
	      clear_split_rec (&oprec);
	      clear_insn_templ (t);
	      return FALSE;
	    }
	}
      else
	e->operand_name = enter_opname (oprec.vec[i]);

      *t->operand_map.tail = e;
      t->operand_map.tail = &e->next;
    }
  clear_split_rec (&oprec);
  return TRUE;
}
