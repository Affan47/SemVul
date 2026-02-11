operator new(size_t size)
{
  char	*file;
  GET_RET_ADDR(file);
  return dmalloc_malloc(file, 0, size, DMALLOC_FUNC_NEW,
			0 , 0 );
}
