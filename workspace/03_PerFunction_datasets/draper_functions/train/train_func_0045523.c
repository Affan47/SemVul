test_odb_packed_one__read_header_0(void)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(packed_objects_one); ++i) {
		git_oid id;
		git_odb_object *obj;
		size_t len;
		git_otype type;

		cl_git_pass(git_oid_fromstr(&id, packed_objects_one[i]));

		cl_git_pass(git_odb_read(&obj, _odb, &id));
		cl_git_pass(git_odb_read_header(&len, &type, _odb, &id));

		cl_assert(obj->raw.len == len);
		cl_assert(obj->raw.type == type);

		git_odb_object_free(obj);
	}
}
