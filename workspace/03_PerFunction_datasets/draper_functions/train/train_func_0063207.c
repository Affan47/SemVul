module_checksimul(int sess_type, REQUEST *request, int maxsimul)
{
	int rcode;

	if(!request->username)
		return 0;

	request->simul_count = 0;
	request->simul_max = maxsimul;
	request->simul_mpp = 1;

	rcode = indexed_modcall(RLM_COMPONENT_SESS, sess_type, request);

	if (rcode != RLM_MODULE_OK) {

		return 0;
	}

	return (request->simul_count < maxsimul) ? 0 : request->simul_mpp;
}
