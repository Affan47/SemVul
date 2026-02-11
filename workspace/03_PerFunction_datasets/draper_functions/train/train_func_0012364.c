math_memory_shift_left_byte(const byte *mem, size_t mem_size, size_t shift, byte *res, size_t res_size)
{
	if (res == NULL)
	{
		res = (byte *) mem;
	}

	if (res_size == 0)
	{
		res_size = mem_size;
	}

	if (shift < mem_size && shift < res_size)
	{
		math_memory_copy(res + shift, res_size - shift, mem, mem_size - shift);
		mem_set(res, 0, shift);
	}
	else
	{
		mem_set(res, 0, res_size);
	}
}
