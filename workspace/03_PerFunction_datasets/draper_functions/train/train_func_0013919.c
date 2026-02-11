dependent_type_p (tree type)
{


  if (!processing_template_decl)
    return false;


  if (!type)
    return true;


  if (type == error_mark_node)
    return false;


  if (!TYPE_DEPENDENT_P_VALID (type))
    {
      TYPE_DEPENDENT_P (type) = dependent_type_p_r (type);
      TYPE_DEPENDENT_P_VALID (type) = 1;
    }

  return TYPE_DEPENDENT_P (type);
}
