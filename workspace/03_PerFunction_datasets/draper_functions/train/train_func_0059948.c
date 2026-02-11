scan_for_self_assignment (const char * dst, etree_type * rhs)
{
  if (rhs == NULL || dst == NULL)
    return FALSE;

  switch (rhs->type.node_class)
    {
    case etree_binary:
      return (scan_for_self_assignment (dst, rhs->binary.lhs)
	      || scan_for_self_assignment (dst, rhs->binary.rhs));

    case etree_trinary:
      return (scan_for_self_assignment (dst, rhs->trinary.lhs)
	      || scan_for_self_assignment (dst, rhs->trinary.rhs));

    case etree_assign:
    case etree_provided:
    case etree_provide:
      if (strcmp (dst, rhs->assign.dst) == 0)
	return TRUE;
      return scan_for_self_assignment (dst, rhs->assign.src);

    case etree_unary:
      return scan_for_self_assignment (dst, rhs->unary.child);

    case etree_value:
      if (rhs->value.str)
	return strcmp (dst, rhs->value.str) == 0;
      return FALSE;

    case etree_name:
      if (rhs->name.name)
	return strcmp (dst, rhs->name.name) == 0;
      return FALSE;

    default:
      break;
    }

  return FALSE;
}
