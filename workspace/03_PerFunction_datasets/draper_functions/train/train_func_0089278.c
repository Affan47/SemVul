talloc_abort(const char *reason)
{
	talloc_log("%s\n", reason);

	if (!talloc_abort_fn) {
		TALLOC_ABORT(reason);
	}

	talloc_abort_fn(reason);
}
