char_eq(x, y)
object x, y;
{
	return(char_code(x) == char_code(y)
	    && char_bits(x) == char_bits(y)
	    && char_font(x) == char_font(y));
}
