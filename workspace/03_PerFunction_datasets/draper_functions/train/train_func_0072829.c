alias_template_specialization_p (const_tree t)
{
  if (t == NULL_TREE)
    return false;

  return (TYPE_P (t)
	  && TYPE_TEMPLATE_INFO (t)
	  && PRIMARY_TEMPLATE_P (TYPE_TI_TEMPLATE (t))
	  && DECL_ALIAS_TEMPLATE_P (TYPE_TI_TEMPLATE (t)));
}
