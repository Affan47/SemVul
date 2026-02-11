encode_attr(const conString *str, int offset)
{
    attr_t oldattrs = 0, attrs;
    int i;
    String *new;

    new = Stringnew(NULL, str->len+1, 0);
    if (!str->charattrs) {
	if (str->attrs)
	    Stringadd(attr2str(Stringcat(new, "@{"), str->attrs), '}');
	for (i = offset; i < str->len; i++) {
	    Stringadd(new, str->data[i]);
	    if (str->data[i] == '@')
		Stringadd(new, '@');
	}
	if (str->attrs)
	    Stringcat(new, "@{n}");
    } else {
	for (i = offset; i < str->len; i++) {
	    attrs = adj_attr(str->attrs, str->charattrs[i]);
	    if ((attrs ^ oldattrs) & F_HWRITE) {
		if (!(attrs & F_HWRITE)) {

		    Stringcat(new, "@{n}");
		} else if (((oldattrs & ~attrs) & F_ENCODE) == 0) {

		    attr_t added = attrs & ~(oldattrs & F_SIMPLE);
		    if (((attrs ^ oldattrs) & F_FGCOLORS) == 0)
			added &= ~F_FGCOLORS;
		    if (((attrs ^ oldattrs) & F_BGCOLORS) == 0)
			added &= ~F_BGCOLORS;
		    Stringadd(attr2str(Stringcat(new, "@{"), added & F_HWRITE),
			'}');
		} else {

		    Stringadd(attr2str(Stringcat(new, "@{n"), attrs & F_HWRITE),
			'}');
		}
	    }
	    Stringadd(new, str->data[i]);
	    if (str->data[i] == '@')
		Stringadd(new, '@');
	    oldattrs = attrs;
	}
	if (attrs & F_HWRITE)
	    Stringcat(new, "@{n}");
    }
    return new;
}
