add_category (tree klass, tree category)
{

  tree cat = lookup_category (klass, CLASS_SUPER_NAME (category));

  if (cat)
    {
      warning (0, "duplicate interface declaration for category %<%E(%E)%>",
	       CLASS_NAME (klass),
	       CLASS_SUPER_NAME (category));
    }
  else
    {
      CLASS_CATEGORY_LIST (category) = CLASS_CATEGORY_LIST (klass);
      CLASS_CATEGORY_LIST (klass) = category;
    }
}
