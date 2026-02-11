reference_compatible_p (tree t1, tree t2)
{


  return (reference_related_p (t1, t2)
	  && at_least_as_qualified_p (t1, t2));
}
