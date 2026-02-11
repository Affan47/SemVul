peek_char(pt, in)
bool pt;
object in;
{
	object c;

	if (pt) {
		do
			c = read_char(in);
		while (cat(c) == cat_whitespace);
		unread_char(c, in);
		return(c);
	} else {
		c = read_char(in);
		unread_char(c, in);
		return(c);
	}
}
