test_validate_glob(void)
{
    gboolean ok = TRUE;
    struct {
	char *glob;
	gboolean should_validate;
    } tests[] = {
	{ "foo.*", TRUE },
	{ "*.txt", TRUE },
	{ "x[abc]y", TRUE },
	{ "x[!abc]y", TRUE },
	{ "[abc", FALSE },
	{ "[!abc", FALSE },
	{ "??*", TRUE },
	{ "**?", TRUE },
	{ "foo\\", FALSE },
	{ "foo\\\\", TRUE },
	{ "(){}+.^$|", TRUE },
	{ "/usr/bin/*", TRUE },
	{ NULL, FALSE },
    }, *t;

    for (t = tests; t->glob; t++) {
	char *validated_err = validate_glob(t->glob);
	if (!validated_err != !!t->should_validate) {
	    ok = FALSE;
	    if (t->should_validate) {
		g_fprintf(stderr, "should have validated glob %s: %s\n",
			t->glob, validated_err);
	    } else {
		g_fprintf(stderr, "unexpectedly validated glob %s\n",
			t->glob);
	    }
	}
    }

    return ok;
}
