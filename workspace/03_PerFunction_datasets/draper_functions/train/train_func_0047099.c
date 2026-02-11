testNameCoding( DirNode &dirNode, bool verbose )
{

    const char *name[] = {
	"1234567",
	"12345678",
	"123456789",
	"123456789ABCDEF",
	"123456789ABCDEF0",
	"123456789ABCDEF01",
	"test-name",
	"test-name2",
	"test",
	"../test",
	"/foo/bar/blah",
	"test-name.21",
	"test-name.22",
	"test-name.o",
	"1.test",
	"2.test",
	"a/b/c/d",
	"a/c/d/e",
	"b/c/d/e",
	"b/a/c/d",
	NULL
    };

    const char **orig = name;
    while(*orig)
    {
	if(verbose)
	    cerr << "   coding name \"" << *orig << "\"";

	string encName = dirNode.relativeCipherPath( *orig );

	if(verbose)
	    cerr << " -> \"" << encName.c_str() << "\"";


	string decName = dirNode.plainPath( encName.c_str() );

	if(decName == *orig)
	{
	    if(verbose)
		cerr << "   OK\n";
	} else
	{
	    if(verbose)
		cerr << "   FAILED (got " << decName << ")\n";
	    return false;
	}

	orig++;
    }

    return true;
}
