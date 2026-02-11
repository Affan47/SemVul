CRYPTO_dbg_malloc(void *addr, int num, const char *file, int line,
	int before_p)
	{
	MEM *m,*mm;
	APP_INFO tmp,*amim;

	switch(before_p & 127)
		{
	case 0:
		break;
	case 1:
		if (addr == NULL)
			break;

		if (is_MemCheck_on())
			{
			MemCheck_off();
			if ((m=(MEM *)OPENSSL_malloc(sizeof(MEM))) == NULL)
				{
				OPENSSL_free(addr);
				MemCheck_on();

				return;
				}
			if (mh == NULL)
				{
				if ((mh=lh_MEM_new()) == NULL)
					{
					OPENSSL_free(addr);
					OPENSSL_free(m);
					addr=NULL;
					goto err;
					}
				}

			m->addr=addr;
			m->file=file;
			m->line=line;
			m->num=num;
			if (options & V_CRYPTO_MDEBUG_THREAD)
				CRYPTO_THREADID_current(&m->threadid);
			else
				memset(&m->threadid, 0, sizeof(m->threadid));

			if (order == break_order_num)
				{

				m->order=order;
				}
			m->order=order++;
#ifdef LEVITTE_DEBUG_MEM
			fprintf(stderr, "LEVITTE_DEBUG_MEM: [%5ld] %c 0x%p (%d)\n",
				m->order,
				(before_p & 128) ? '*' : '+',
				m->addr, m->num);
#endif
			if (options & V_CRYPTO_MDEBUG_TIME)
				m->time=time(NULL);
			else
				m->time=0;

			CRYPTO_THREADID_current(&tmp.threadid);
			m->app_info=NULL;
			if (amih != NULL
			    && (amim=lh_APP_INFO_retrieve(amih,&tmp)) != NULL)
				{
				m->app_info = amim;
				amim->references++;
				}

			if ((mm=lh_MEM_insert(mh, m)) != NULL)
				{

				if (mm->app_info != NULL)
					{
					mm->app_info->references--;
					}
				OPENSSL_free(mm);
				}
		err:
			MemCheck_on();

			}
		break;
		}
	return;
	}
