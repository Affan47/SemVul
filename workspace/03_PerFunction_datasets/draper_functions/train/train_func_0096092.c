do_literal(uschar *p)
{
if (Ustrcmp(p, "layout") == 0) literal_state = LITERAL_LAYOUT;
else if (Ustrcmp(p, "text") == 0) literal_state = LITERAL_TEXT;
else if (Ustrcmp(p, "off") == 0) literal_state = LITERAL_OFF;
else if (Ustrcmp(p, "xml") == 0) literal_state = LITERAL_XML;
else error(5, p);
}
