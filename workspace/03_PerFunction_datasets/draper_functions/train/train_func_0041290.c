indent(struct twojson *j)
{
    size_t i = j->indent;
    if (j->flags & HEIM_JSON_F_ONE_LINE)
	return;
    while (i--)
	j->out(j->ctx, "\t");
}
