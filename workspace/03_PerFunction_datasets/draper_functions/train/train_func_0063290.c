xisprint(int c)
{
    switch (c) {
    case 169:
	return 1;
    default:
	return isprint(c);
    }
}
