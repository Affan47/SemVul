cb_emit_perform (cb_tree perform, cb_tree body)
{
	if (perform == cb_error_node) {
		return;
	}
	CB_PERFORM (perform)->body = body;
	cb_emit (perform);
}
