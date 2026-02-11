unqliteCoreInitialize(void)
{
	const unqlite_kv_methods *pMethods;
	const unqlite_vfs *pVfs;
#if defined(UNQLITE_ENABLE_THREADS)
	const SyMutexMethods *pMutexMethods = 0;
	SyMutex *pMaster = 0;
#endif
	int rc;


	if( sUnqlMPGlobal.nMagic == UNQLITE_LIB_MAGIC ){
		return UNQLITE_OK;
	}

	pVfs = unqliteExportBuiltinVfs();

	unqlite_lib_config(UNQLITE_LIB_CONFIG_VFS, pVfs);
#if defined(UNQLITE_ENABLE_THREADS)
	if( sUnqlMPGlobal.nThreadingLevel != UNQLITE_THREAD_LEVEL_SINGLE ){
		pMutexMethods = sUnqlMPGlobal.pMutexMethods;
		if( pMutexMethods == 0 ){

			pMutexMethods = SyMutexExportMethods();
			if( pMutexMethods == 0 ){
				return UNQLITE_CORRUPT;
			}

			rc = unqlite_lib_config(UNQLITE_LIB_CONFIG_USER_MUTEX, pMutexMethods);
			if( rc != UNQLITE_OK ){
				return rc;
			}
		}

		pMaster = SyMutexNew(pMutexMethods, SXMUTEX_TYPE_STATIC_1);
		if( pMaster == 0 ){
			return UNQLITE_CORRUPT;
		}
	}

	rc = UNQLITE_OK;
	SyMutexEnter(pMutexMethods, pMaster);
	if( sUnqlMPGlobal.nMagic != UNQLITE_LIB_MAGIC ){
#endif
		if( sUnqlMPGlobal.sAllocator.pMethods == 0 ){

			rc = unqlite_lib_config(UNQLITE_LIB_CONFIG_USER_MALLOC, 0);
			if( rc != UNQLITE_OK ){

				goto End;
			}
		}
#if defined(UNQLITE_ENABLE_THREADS)
		if( sUnqlMPGlobal.nThreadingLevel > UNQLITE_THREAD_LEVEL_SINGLE ){

			rc = SyMemBackendMakeThreadSafe(&sUnqlMPGlobal.sAllocator, sUnqlMPGlobal.pMutexMethods);
			if( rc != UNQLITE_OK ){
				goto End;
			}
		}
#endif
		SySetInit(&sUnqlMPGlobal.kv_storage,&sUnqlMPGlobal.sAllocator,sizeof(unqlite_kv_methods *));

		pMethods = unqliteExportMemKvStorage();
		unqlite_lib_config(UNQLITE_LIB_CONFIG_STORAGE_ENGINE,pMethods);

		pMethods = unqliteExportDiskKvStorage();
		unqlite_lib_config(UNQLITE_LIB_CONFIG_STORAGE_ENGINE,pMethods);

		if( sUnqlMPGlobal.iPageSize < UNQLITE_MIN_PAGE_SIZE ){
			unqlite_lib_config(UNQLITE_LIB_CONFIG_PAGE_SIZE,UNQLITE_DEFAULT_PAGE_SIZE);
		}

		sUnqlMPGlobal.nMagic = UNQLITE_LIB_MAGIC;
		rc = UNQLITE_OK;
#if defined(UNQLITE_ENABLE_THREADS)
	}
#endif
End:
#if defined(UNQLITE_ENABLE_THREADS)

	SyMutexLeave(pMutexMethods, pMaster);
#endif
	return rc;
}
