sb_return(SB *sb, void **data_out, size_t *length_out)
{
	*sb->cur = 0;
	if (data_out)
		*data_out = sb->start;
	else
		free(sb->start);
	if (length_out)
		*length_out = sb->cur - sb->start;
}
