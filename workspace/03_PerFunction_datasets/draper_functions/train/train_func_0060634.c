put_web (struct web *web, enum node_type type)
{
  switch (type)
    {
      case INITIAL:
      case FREE:
      case FREEZE:
      case SPILL:
      case SPILLED:
      case COALESCED:
      case COLORED:
      case SELECT:
	push_list (web->dlink, &WEBS(type));
	break;
      case PRECOLORED:
	push_list (web->dlink, &WEBS(INITIAL));
	break;
      case SIMPLIFY:
	if (web->spill_temp)
	  push_list (web->dlink, &WEBS(type = SIMPLIFY_SPILL));
	else if (web->add_hardregs)
	  push_list (web->dlink, &WEBS(type = SIMPLIFY_FAT));
	else
	  push_list (web->dlink, &WEBS(SIMPLIFY));
	break;
      default:
	abort ();
    }
  web->type = type;
}
