htescape(struct html *ctx, const char *s, int n, int italics)
{
    while (n > 0 && *s) {
	unsigned char c = (unsigned char)*s++;

	if (c == '&')
	    htprintf(ctx, "&amp;");
	else if (c == '<')
	    htprintf(ctx, "&lt;");
	else if (c == '>')
	    htprintf(ctx, "&gt;");
	else if (c >= ' ' && c < '\177')
	    htprintf(ctx, "%c", c);
	else {
	    if (italics) htprintf(ctx, "<i>");
	    htprintf(ctx, "[%02x]", c);
	    if (italics) htprintf(ctx, "</i>");
	}

	n--;
    }
}
