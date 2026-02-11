attribute_create(int oid, chunk_t value)
{
	attribute_t *this;

	INIT(this,
		.oid = oid,
		.value = chunk_clone(value),
	);

	return this;
}
