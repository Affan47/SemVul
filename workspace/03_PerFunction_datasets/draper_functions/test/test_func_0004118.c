test_atom_category_escaping (void)
{
	GDataCategory *category;

	category = gdata_category_new ("<term>", "http://foo.com?foo&bar", "Label & Stuff");


	gdata_test_assert_xml (category,
	                 "<?xml version='1.0' encoding='UTF-8'?>"
	                 "<category xmlns='http://www.w3.org/2005/Atom' term='&lt;term&gt;' scheme='http://foo.com?foo&amp;bar' "
				"label='Label &amp; Stuff'/>");
	g_object_unref (category);
}
