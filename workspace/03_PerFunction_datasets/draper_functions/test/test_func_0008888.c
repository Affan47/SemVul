put_col(const Str &key, int col, const Str &value) {
    while (failing)
	;
#if !MASSTREE_ROW_TYPE_STR
    if (!kvo_)
	kvo_ = new_kvout(-1, 2048);
    Json req[2] = {Json(col), Json(String::make_stable(value))};
    (void) q_[0].run_put(tree->table(), key, &req[0], &req[2], *ti_);
    if (ti_->ti_log)
	ti_->ti_log->record(logcmd_put, q_[0].query_times(), key,
                            &req[0], &req[2]);
#else
    (void) key, (void) col, (void) value;
    assert(0);
#endif
}
