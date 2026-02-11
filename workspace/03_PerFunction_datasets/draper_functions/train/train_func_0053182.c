vpc_probe(const uint8_t *buf, int buf_size, const char *filename)
{
    if (buf_size >= 8 && !strncmp((char *)buf, "conectix", 8))
	return 100;
    return 0;
}
