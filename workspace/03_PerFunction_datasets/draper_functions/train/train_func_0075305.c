read_mem(
	const struct fauhdli_process *s,
	union fauhdli_value *ret,
	void *mem,
	enum type_kind type
)
{
	switch (type) {
	case TYPE_INT:
		ret->univ_int = *(universal_integer*)mem;
		break;

	case TYPE_FLOAT:
		ret->univ_real = *(universal_real*)mem;
		break;

	case TYPE_POINTER:
		ret->pointer = *(void **)mem;
		break;
	}
}
