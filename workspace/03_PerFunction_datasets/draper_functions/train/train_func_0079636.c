currently_open_class (tree t)
{
  int i;

  if (!CLASS_TYPE_P (t))
    return false;

  t = TYPE_MAIN_VARIANT (t);


  for (i = current_class_depth; i > 0; --i)
    {
      tree c;
      if (i == current_class_depth)
	c = current_class_type;
      else
	{
	  if (current_class_stack[i].hidden)
	    break;
	  c = current_class_stack[i].type;
	}
      if (!c)
	continue;
      if (same_type_p (c, t))
	return true;
    }
  return false;
}
