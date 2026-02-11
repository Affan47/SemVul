make_ptrmem_declarator (cp_cv_quals cv_qualifiers, tree class_type,
			cp_declarator *pointee,
			tree attributes)
{
  cp_declarator *declarator;

  declarator = make_declarator (cdk_ptrmem);
  declarator->declarator = pointee;
  declarator->u.pointer.qualifiers = cv_qualifiers;
  declarator->u.pointer.class_type = class_type;

  if (pointee)
    {
      declarator->parameter_pack_p = pointee->parameter_pack_p;
      pointee->parameter_pack_p = false;
    }
  else
    declarator->parameter_pack_p = false;

  declarator->std_attributes = attributes;

  return declarator;
}
