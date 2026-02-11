configured_ident(git_signature **out, const git_repository *repo)
{
	if (repo->ident_name && repo->ident_email)
		return git_signature_now(out, repo->ident_name, repo->ident_email);


	return -1;
}
