dbmw_foreach_remove(dbmw_t *dw, dbmw_cbr_t cbr, void *arg)
{
	struct foreach_ctx ctx;
	struct cache_foreach_ctx fctx;
	size_t pruned;

	dbmw_check(dw);

	if (dbg_ds_debugging(dw->dbg, 1, DBG_DSF_ITERATOR)) {
		dbg_ds_log(dw->dbg, dw, "%s: starting with %s(%p)", G_STRFUNC,
			stacktrace_function_name(cbr), arg);
	}


	dbmw_sync(dw, DBMW_SYNC_CACHE | DBMW_DELETED_ONLY);


	ctx.u.cbr = cbr;
	ctx.arg = arg;
	ctx.dw = dw;

	map_foreach(dw->values, cache_reset_before_traversal, NULL);
	pruned = dbmap_foreach_remove(dw->dm, dbmw_foreach_remove_trampoline, &ctx);

	ZERO(&fctx);
	fctx.removing = TRUE;
	fctx.foreach = &ctx;
	fctx.u.cbr = dbmw_foreach_remove_trampoline;


	map_foreach(dw->values, cache_finish_traversal, &fctx);
	map_foreach_remove(dw->values, cache_free_removable, dw);
	dw->cached = fctx.cached;
	dw->count_needs_sync = FALSE;

	if (dbg_ds_debugging(dw->dbg, 1, DBG_DSF_ITERATOR)) {
		dbg_ds_log(dw->dbg, dw, "%s: done with %s(%p): "
			"pruned %zu from dbmap, %zu from cache (%zu total), "
			"has %zu unflushed entr%s in cache",
			G_STRFUNC,
			stacktrace_function_name(cbr), arg,
			pruned, fctx.removed, pruned + fctx.removed,
			dw->cached, 1 == dw->cached ? "y" : "ies");
	}

	return pruned + fctx.removed;
}
