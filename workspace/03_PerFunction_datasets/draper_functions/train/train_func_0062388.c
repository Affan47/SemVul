NextChar()
{
	return (*pos == 0 ? -1: (int)(unsigned char)*pos++);
}
