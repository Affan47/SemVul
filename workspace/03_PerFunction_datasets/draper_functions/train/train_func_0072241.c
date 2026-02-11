nabors(void)
{
    int count = 0;

    if (tl)
	count++;
    if (tc)
	count++;
    if (tr)
	count++;
    if (mr)
	count++;
    if (br)
	count++;
    if (bc)
	count++;
    if (bl)
	count++;
    if (ml)
	count++;

    return (count);
}
