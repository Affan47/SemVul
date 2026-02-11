cos_cache_release(cos_cache *ptheCache)
{
	int ret = 0;
	int destroy = 0;
	cosCache *pOldCache = (cosCache*)ptheCache;

	LDAPDebug( LDAP_DEBUG_TRACE, "--> cos_cache_release\n",0,0,0);

	slapi_lock_mutex(cache_lock);

	if(pOldCache)
	{
		ret = --(pOldCache->refCount);
		if(ret == 0)
			destroy = 1;
	}

	slapi_unlock_mutex(cache_lock);

	if(destroy)
	{
		cosDefinitions *pDef = pOldCache->pDefs;


		if(pCache && pCache->vattr_cacheable)
		{
			slapi_vattrcache_cache_all();
		}


		if(pDef)
			cos_cache_del_schema(pOldCache);

		while(pDef)
		{
			cosDefinitions *pTmpD = pDef;
			cosTemplates *pCosTmps = pDef->pCosTmps;

			while(pCosTmps)
			{
				cosTemplates *pTmpT = pCosTmps;

				pCosTmps = pCosTmps->list.pNext;

				cos_cache_del_attr_list(&(pTmpT->pAttrs));
				cos_cache_del_attrval_list(&(pTmpT->pObjectclasses));
				cos_cache_del_attrval_list(&(pTmpT->pDn));
				slapi_ch_free((void**)&(pTmpT->cosGrade));
				slapi_ch_free((void**)&pTmpT);
			}

			pDef = pDef->list.pNext;

			cos_cache_del_attrval_list(&(pTmpD->pDn));
			cos_cache_del_attrval_list(&(pTmpD->pCosTargetTree));
			cos_cache_del_attrval_list(&(pTmpD->pCosTemplateDn));
			cos_cache_del_attrval_list(&(pTmpD->pCosSpecifier));
			cos_cache_del_attrval_list(&(pTmpD->pCosAttrs));
			cos_cache_del_attrval_list(&(pTmpD->pCosOverrides));
			cos_cache_del_attrval_list(&(pTmpD->pCosOperational));
			cos_cache_del_attrval_list(&(pTmpD->pCosMerge));
			cos_cache_del_attrval_list(&(pTmpD->pCosOpDefault));
			slapi_ch_free((void**)&pTmpD);
		}

		if(pOldCache->ppAttrIndex)
			slapi_ch_free((void**)&(pOldCache->ppAttrIndex));
		if(pOldCache->ppTemplateList)
			slapi_ch_free((void**)&(pOldCache->ppTemplateList));
		slapi_ch_free((void**)&pOldCache);
	}

	LDAPDebug( LDAP_DEBUG_TRACE, "<-- cos_cache_release\n",0,0,0);

	return ret;
}
