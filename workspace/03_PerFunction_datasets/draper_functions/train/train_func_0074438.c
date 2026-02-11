repack(const char* filename, const char* new_file)
{
	int res = 0;
	char* pass = 0;
	struct pres_file_t* p = _open_pres_container(filename, 0, &pass);

	if (!p)
		goto err_out;

	res = k_pres_repack(p, new_file, pass);
	if (res)
		goto err_out;

	goto out;
err_out:
	perror("repack");
	res = -1;
out:
	if (pass)
		free(pass);
	if (p)
		_close_pres_container(p);
	return res;
}
