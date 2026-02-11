math_memory_div2(byte *left, size_t lsize, const byte *right, size_t rsize, byte *res, size_t res_size, int base)
{
	byte buff[lsize];
	char text[1024];

	if (res && res != left)
	{
		math_memory_copy(buff, lsize, left, lsize);
		res_size = math_memory_div(buff, lsize, right, rsize, res, res_size);

		math_memory_remain2text(buff, lsize, right, rsize, text, sizeof(text), base, 0, 0);
		println("remain = 0.%s", text);
	}
	else
	{
		res_size = math_memory_div((byte *) left, lsize, right, rsize, buff, lsize);
		math_memory_show("Remainder = ", left, lsize, base);
		math_memory_copy((byte *) left, lsize, buff, lsize);
	}

	return res_size;
}
