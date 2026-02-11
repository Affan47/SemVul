ll_binary_merge(const struct ll_merge_driver *drv_unused,
			   mmbuffer_t *result,
			   const char *path_unused,
			   mmfile_t *orig,
			   mmfile_t *src1, const char *name1,
			   mmfile_t *src2, const char *name2,
			   int virtual_ancestor)
{


	mmfile_t *stolen = virtual_ancestor ? orig : src1;

	result->ptr = stolen->ptr;
	result->size = stolen->size;
	stolen->ptr = NULL;
	return 1;
}
