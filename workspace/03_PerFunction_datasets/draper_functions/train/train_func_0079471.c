section_symbol (segT sec)
{
  segment_info_type *seginfo = seg_info (sec);
  symbolS *s;

  if (seginfo == 0)
    abort ();
  if (seginfo->sym)
    return seginfo->sym;

#ifndef EMIT_SECTION_SYMBOLS
#define EMIT_SECTION_SYMBOLS 1
#endif

  if (! EMIT_SECTION_SYMBOLS || symbol_table_frozen)
    {

      s = symbol_create (sec->symbol->name, sec, 0, &zero_address_frag);
    }
  else
    {
      segT seg;
      s = symbol_find (sec->symbol->name);


      if (s == NULL
	  || ((seg = S_GET_SEGMENT (s)) != sec
	      && seg != undefined_section))
	s = symbol_new (sec->symbol->name, sec, 0, &zero_address_frag);
      else if (seg == undefined_section)
	{
	  S_SET_SEGMENT (s, sec);
	  symbol_set_frag (s, &zero_address_frag);
	}
    }

  S_CLEAR_EXTERNAL (s);


  if (obj_sec_sym_ok_for_reloc (sec))
    symbol_set_bfdsym (s, sec->symbol);
  else
    symbol_get_bfdsym (s)->flags |= BSF_SECTION_SYM;

  seginfo->sym = s;
  return s;
}
