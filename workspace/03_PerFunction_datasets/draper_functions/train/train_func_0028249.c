operator=(const geometry_batcher &geo)
{
	if (this != &geo) {
		clone(geo);
	}

	return *this;
}
