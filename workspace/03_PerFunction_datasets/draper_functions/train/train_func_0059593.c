mono_patch_info_dup_mp (MonoMemPool *mp, MonoJumpInfo *patch_info)
{
	MonoJumpInfo *res = mono_mempool_alloc (mp, sizeof (MonoJumpInfo));
	memcpy (res, patch_info, sizeof (MonoJumpInfo));

	switch (patch_info->type) {
	case MONO_PATCH_INFO_RVA:
	case MONO_PATCH_INFO_LDSTR:
	case MONO_PATCH_INFO_TYPE_FROM_HANDLE:
	case MONO_PATCH_INFO_LDTOKEN:
	case MONO_PATCH_INFO_DECLSEC:
		res->data.token = mono_mempool_alloc (mp, sizeof (MonoJumpInfoToken));
		memcpy (res->data.token, patch_info->data.token, sizeof (MonoJumpInfoToken));
		break;
	case MONO_PATCH_INFO_SWITCH:
		res->data.table = mono_mempool_alloc (mp, sizeof (MonoJumpInfoBBTable));
		memcpy (res->data.table, patch_info->data.table, sizeof (MonoJumpInfoBBTable));
		res->data.table->table = mono_mempool_alloc (mp, sizeof (MonoBasicBlock*) * patch_info->data.table->table_size);
		memcpy (res->data.table->table, patch_info->data.table->table, sizeof (MonoBasicBlock*) * patch_info->data.table->table_size);
		break;
	case MONO_PATCH_INFO_RGCTX_FETCH:
		res->data.rgctx_entry = mono_mempool_alloc (mp, sizeof (MonoJumpInfoRgctxEntry));
		memcpy (res->data.rgctx_entry, patch_info->data.rgctx_entry, sizeof (MonoJumpInfoRgctxEntry));
		res->data.rgctx_entry->data = mono_patch_info_dup_mp (mp, res->data.rgctx_entry->data);
		break;
	case MONO_PATCH_INFO_DELEGATE_TRAMPOLINE:
		res->data.del_tramp = mono_mempool_alloc0 (mp, sizeof (MonoClassMethodPair));
		memcpy (res->data.del_tramp, patch_info->data.del_tramp, sizeof (MonoClassMethodPair));
		break;
	case MONO_PATCH_INFO_GSHAREDVT_CALL:
		res->data.gsharedvt = mono_mempool_alloc (mp, sizeof (MonoJumpInfoGSharedVtCall));
		memcpy (res->data.gsharedvt, patch_info->data.gsharedvt, sizeof (MonoJumpInfoGSharedVtCall));
		break;
	case MONO_PATCH_INFO_GSHAREDVT_METHOD: {
		MonoGSharedVtMethodInfo *info;
		MonoGSharedVtMethodInfo *oinfo;
		int i;

		oinfo = patch_info->data.gsharedvt_method;
		info = mono_mempool_alloc (mp, sizeof (MonoGSharedVtMethodInfo));
		res->data.gsharedvt_method = info;
		memcpy (info, oinfo, sizeof (MonoGSharedVtMethodInfo));
		info->entries = mono_mempool_alloc (mp, sizeof (MonoRuntimeGenericContextInfoTemplate) * info->count_entries);
		for (i = 0; i < oinfo->num_entries; ++i) {
			MonoRuntimeGenericContextInfoTemplate *otemplate = &oinfo->entries [i];
			MonoRuntimeGenericContextInfoTemplate *template = &info->entries [i];

			memcpy (template, otemplate, sizeof (MonoRuntimeGenericContextInfoTemplate));
		}


		break;
	}
	default:
		break;
	}

	return res;
}
