sbcat(sb, string, len)
    str_buf	*sb;
    char	*string;
    int		len;
{
    if (sb != NULL) {
	if (sbinsure(sb, sb->len+len) == NULL)
	    return NULL;
	strncpy(sb->buf+sb->len, string, len);
	sb->len	+= len;
    }

    return sb;
}
