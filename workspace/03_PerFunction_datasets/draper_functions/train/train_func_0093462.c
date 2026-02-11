operator new (size_t size, const std::nothrow_t&) throw()
{
	return vm_malloc_q(size);
}
