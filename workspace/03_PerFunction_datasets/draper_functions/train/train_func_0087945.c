test_separators()
{
    const char *p;


    {
	tok_t t("one/two three,four", "/");

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "one"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "two three,four"));

	p = t.next();
	check(p == 0);
    }


    {
	tok_t t("one/two three,four", " ,");

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "one/two"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "three"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "four"));

	p = t.next();
	check(p == 0);
    }


    {
	tok_t t("one,,,,,two,,three", ",");

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "one"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "two"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "three"));

	p = t.next();
	check(p == 0);
    }


    {
	tok_t t(",,,,one,two,three,,,", ",");

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "one"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "two"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "three"));

	p = t.next();
	check(p == 0);
    }


    {
	tok_t t(",", ",");

	p = t.next();
	check(p == 0);
    }


    {
	tok_t t(",,,,,,", ",");

	p = t.next();
	check(p == 0);
    }
}
