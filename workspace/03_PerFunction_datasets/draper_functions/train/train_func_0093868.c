test_corner_cases()
{
    const char *p;


    {
	tok_t t((const char *)0, "/");
	p = t.next();
	check(p == 0);
    }


    {
	tok_t t("alpha beta\tgamma\rdelta\nepsilon", 0);

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "alpha"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "beta"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "gamma"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "delta"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "epsilon"));

	p = t.next();
	check(p == 0);
    }


    {
	tok_t t("alpha beta\tgamma\rdelta\nepsilon");

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "alpha"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "beta"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "gamma"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "delta"));

	p = t.next();
	check(p != 0);
	check(!strcmp(p, "epsilon"));

	p = t.next();
	check(p == 0);
    }
}
