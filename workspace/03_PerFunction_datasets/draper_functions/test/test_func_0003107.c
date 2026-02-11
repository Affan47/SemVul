bam_aux2Z(const uint8_t *s)
{
	int type;
	type = *s++;
	if (type == 'Z' || type == 'H') return (char*)s;
	else return 0;
}
