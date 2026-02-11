cswift_init(ENGINE *e)
	{
        SW_CONTEXT_HANDLE hac;
        t_swAcquireAccContext *p1;
        t_swAttachKeyParam *p2;
        t_swSimpleRequest *p3;
        t_swReleaseAccContext *p4;

	if(cswift_dso != NULL)
		{
		CSWIFTerr(CSWIFT_F_CSWIFT_INIT,CSWIFT_R_ALREADY_LOADED);
		goto err;
		}

	cswift_dso = DSO_load(NULL, get_CSWIFT_LIBNAME(), NULL, 0);
	if(cswift_dso == NULL)
		{
		CSWIFTerr(CSWIFT_F_CSWIFT_INIT,CSWIFT_R_NOT_LOADED);
		goto err;
		}
	if(!(p1 = (t_swAcquireAccContext *)
				DSO_bind_func(cswift_dso, CSWIFT_F1)) ||
			!(p2 = (t_swAttachKeyParam *)
				DSO_bind_func(cswift_dso, CSWIFT_F2)) ||
			!(p3 = (t_swSimpleRequest *)
				DSO_bind_func(cswift_dso, CSWIFT_F3)) ||
			!(p4 = (t_swReleaseAccContext *)
				DSO_bind_func(cswift_dso, CSWIFT_F4)))
		{
		CSWIFTerr(CSWIFT_F_CSWIFT_INIT,CSWIFT_R_NOT_LOADED);
		goto err;
		}

	p_CSwift_AcquireAccContext = p1;
	p_CSwift_AttachKeyParam = p2;
	p_CSwift_SimpleRequest = p3;
	p_CSwift_ReleaseAccContext = p4;


	if(!get_context(&hac))
		{
		CSWIFTerr(CSWIFT_F_CSWIFT_INIT,CSWIFT_R_UNIT_FAILURE);
		goto err;
		}
	release_context(hac);

	return 1;
err:
	if(cswift_dso)
	{
		DSO_free(cswift_dso);
		cswift_dso = NULL;
	}
	p_CSwift_AcquireAccContext = NULL;
	p_CSwift_AttachKeyParam = NULL;
	p_CSwift_SimpleRequest = NULL;
	p_CSwift_ReleaseAccContext = NULL;
	return 0;
	}
