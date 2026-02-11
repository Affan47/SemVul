test_refs_read__nested_symbolic(void)
{

	git_reference *reference, *resolved_ref;
	git_object *object;
	git_oid id;

	cl_git_pass(git_reference_lookup(&reference, g_repo, head_tracker_sym_ref_name));
	cl_assert(git_reference_type(reference) & GIT_REF_SYMBOLIC);
	cl_assert(reference_is_packed(reference) == 0);
	cl_assert_equal_s(reference->name, head_tracker_sym_ref_name);

	cl_git_pass(git_reference_resolve(&resolved_ref, reference));
	cl_assert(git_reference_type(resolved_ref) == GIT_REF_OID);

	cl_git_pass(git_object_lookup(&object, g_repo, git_reference_target(resolved_ref), GIT_OBJ_ANY));
	cl_assert(object != NULL);
	cl_assert(git_object_type(object) == GIT_OBJ_COMMIT);

	git_oid_fromstr(&id, current_master_tip);
	cl_assert(git_oid_cmp(&id, git_object_id(object)) == 0);

	git_object_free(object);

	git_reference_free(reference);
	git_reference_free(resolved_ref);
}
