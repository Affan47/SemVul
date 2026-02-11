operator new[](size_t nbytes, std::nothrow_t &)
    throw()
{
    return mem_alloc(nbytes);
}
