ssh_key_free(struct git_cred *cred)
{
	git_cred_ssh_key *c =
		(git_cred_ssh_key *)cred;

	git__free(c->username);

	if (c->privatekey) {

		size_t key_len = strlen(c->privatekey);
		git__memzero(c->privatekey, key_len);
		git__free(c->privatekey);
	}

	if (c->passphrase) {

		size_t pass_len = strlen(c->passphrase);
		git__memzero(c->passphrase, pass_len);
		git__free(c->passphrase);
	}

	if (c->publickey) {

		size_t key_len = strlen(c->publickey);
		git__memzero(c->publickey, key_len);
		git__free(c->publickey);
	}

	git__free(c);
}
