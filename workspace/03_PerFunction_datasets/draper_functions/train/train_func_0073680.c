onListingEnd(void )
{
	if (lastTestCase != NULL)
		*out << "\t</TestCase>" << endl;

	*out << "</UnitTestList>" << endl;
}
