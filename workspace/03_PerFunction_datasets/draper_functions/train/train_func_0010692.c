acl_free(void *obj_p)
{
	obj_prefix *int_p = ((obj_prefix *)obj_p)-1;
	if (!obj_p || !int_p) {
		errno = EINVAL;
		return -1;
	}


	switch(int_p->p_magic) {
		case acl_MAGIC:
			__acl_free_acl_obj((acl_obj *)int_p);
			return 0;
		case qualifier_MAGIC:
		case string_MAGIC:
			free_obj_p(int_p);
			return 0;
		case acl_entry_MAGIC:
		case acl_permset_MAGIC:
#ifdef LIBACL_DEBUG
			fprintf(stderr, "object (magic=0x%X) "
			        "at %p cannot be freed\n",
				int_p->p_magic, int_p);
#endif
			break;
		default:
#ifdef LIBACL_DEBUG
			fprintf(stderr, "invalid object (magic=0x%X) "
			        "at %p\n", int_p->p_magic, int_p);
#endif
			break;
	}
	errno = EINVAL;
	return -1;
}
