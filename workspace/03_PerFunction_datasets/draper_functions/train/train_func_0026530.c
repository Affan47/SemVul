is_interesting_object (void const* ptr)
{
	if (ptr == 0) {
		return false;
	}

	return interesting_pointers().find (ptr) != interesting_pointers().end();
}
