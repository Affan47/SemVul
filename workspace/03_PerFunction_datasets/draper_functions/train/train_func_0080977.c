char_equal(x, y)
object x, y;
{
	int i, j;

	i = char_code(x);
	j = char_code(y);
	if (isLower(i))
		i -= 'a' - 'A';
	if (isLower(j))
		j -= 'a' - 'A';
	return(i == j);
}
