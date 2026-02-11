nonimpexpres()
{
    expres();
    if (lastexp.data & IMPBIT)
	experror(NONIMPREQ);
}
