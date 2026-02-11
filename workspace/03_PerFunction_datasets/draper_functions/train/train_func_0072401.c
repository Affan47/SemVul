title(const char *t1, const char *t2)
{
    if (!t1)
        t1 = "";
    if (!t2)
        t2 = "";
    trace(("wide_output_header::title(this = %08lX, \"%s\", \"%s\")\n{\n",
        (long)this, t1, t2));
    title1 = censor(t1);
    title2 = censor(t2);
    trace(("}\n"));
}
