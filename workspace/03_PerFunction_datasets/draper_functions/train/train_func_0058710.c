chirp_reli_setrep(const char *host, const char *path, int nreps, time_t stoptime )
{


	if(!strcmp(path,"@@@")) chirp_reli_default_nreps = nreps;
	RETRY_ATOMIC( result = chirp_client_setrep(client,path,nreps,stoptime); )
}
