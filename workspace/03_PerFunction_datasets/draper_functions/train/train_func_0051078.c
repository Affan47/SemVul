test_trim_nuls()
{
    subtest("trim_nuls, empty string");
    {
	estring e;

	check(e.length() == 0);
	check(e.data() == 0);
	e.trim_nuls();
	check(e.length() == 0);
	check(e.data() == 0);
    }

    subtest("trim_nuls, non-empty string");
    {
	const char x[] = "trapped beneath my piano";
	estring e(x);

	check(e.length() == 24);
	check(!strcmp(e.data(), x));
	check(e.data()[24] == '\0');
	check(strlen(e.data()) == 24);
	check(e.data() != x);
	check(is_heap(e.data()));

	e.trim_nuls();

	check(e.length() == 24);
	check(!strcmp(e.data(), x));
	check(e.data()[24] == '\0');
	check(strlen(e.data()) == 24);
	check(e.data() != x);
	check(is_heap(e.data()));
    }

    subtest("trim_nuls, non-empty string with trailing nuls");
    {
	char *x = (char *)calloc(33, 1);
	strcpy(x, "scares the");
	estring e(x, 32);

	check(e.length() == 32);
	check(e.data() == x);
	check(!strcmp(e.data(), "scares the"));
	check(strlen(e.data()) == 10);

	e.trim_nuls();

	check(e.length() == 10);
	check(e.data() == x);
	check(!strcmp(e.data(), "scares the"));
	check(strlen(e.data()) == 10);
    }
}
