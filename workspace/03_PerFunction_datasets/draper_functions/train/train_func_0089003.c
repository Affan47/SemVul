ast_pickup_call(struct ast_channel *chan)
{
	struct ast_channel *target;
	int res = -1;

	ast_debug(1, "pickup attempt by %s\n", ast_channel_name(chan));


	target = ast_pickup_find_by_group(chan);
	if (target) {
		ast_log(LOG_NOTICE, "pickup %s attempt by %s\n", ast_channel_name(target), ast_channel_name(chan));

		res = ast_do_pickup(chan, target);
		ast_channel_unlock(target);
		if (!res) {
			if (!ast_strlen_zero(pickupsound)) {
				pbx_builtin_setvar_helper(target, "BRIDGE_PLAY_SOUND", pickupsound);
			}
		} else {
			ast_log(LOG_WARNING, "pickup %s failed by %s\n", ast_channel_name(target), ast_channel_name(chan));
		}
		target = ast_channel_unref(target);
	}

	if (res < 0) {
		ast_debug(1, "No call pickup possible... for %s\n", ast_channel_name(chan));
		if (!ast_strlen_zero(pickupfailsound)) {
			ast_answer(chan);
			ast_stream_and_wait(chan, pickupfailsound, "");
		}
	}

	return res;
}
