test_online_push__notes(void)
{
	git_oid note_oid, *target_oid, expected_oid;
	git_signature *signature;
	const char *specs[] = { "refs/notes/commits:refs/notes/commits" };
	push_status exp_stats[] = { { "refs/notes/commits", 1 } };
	expected_ref exp_refs[] = { { "refs/notes/commits", &expected_oid } };
	const char *specs_del[] = { ":refs/notes/commits" };

	git_oid_fromstr(&expected_oid, "8461a99b27b7043e58ff6e1f5d2cf07d282534fb");

	target_oid = &_oid_b6;


	cl_git_pass(git_signature_new(&signature, "nulltoken", "emeric.fermas@gmail.com", 1323847743, 60));
	cl_git_pass(git_note_create(&note_oid, _repo, signature, signature, NULL, target_oid, "hello world\n", 0));

	do_push(specs, ARRAY_SIZE(specs),
		exp_stats, ARRAY_SIZE(exp_stats),
		exp_refs, ARRAY_SIZE(exp_refs), 0, 1, 1);


	do_push(specs_del, ARRAY_SIZE(specs_del),
		exp_stats, 1,
		NULL, 0, 0, 0, 0);

	git_signature_free(signature);
}
