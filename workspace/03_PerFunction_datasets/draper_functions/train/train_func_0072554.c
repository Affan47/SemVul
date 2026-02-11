sgen_los_free_object (LOSObject *obj)
{
#ifndef LOS_DUMMY
	size_t size = obj->size;
	SGEN_LOG (4, "Freed large object %p, size %lu", obj->data, (unsigned long)obj->size);
	binary_protocol_empty (obj->data, obj->size);

	los_memory_usage -= size;
	los_num_objects--;

#ifdef USE_MALLOC
	free (obj);
#else
	if (size > LOS_SECTION_OBJECT_LIMIT) {
		if (!pagesize)
			pagesize = mono_pagesize ();
		size += sizeof (LOSObject);
		size += pagesize - 1;
		size &= ~(pagesize - 1);
		sgen_free_os_memory (obj, size, SGEN_ALLOC_HEAP);
		sgen_memgov_release_space (size, SPACE_LOS);
	} else {
		free_los_section_memory (obj, size + sizeof (LOSObject));
#ifdef LOS_CONSISTENCY_CHECKS
		los_consistency_check ();
#endif
	}
#endif
#endif
}
