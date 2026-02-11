local_indicate(struct ast_channel *ast, int condition, const void *data, size_t datalen)
{
	struct local_pvt *p = ast_channel_tech_pvt(ast);
	int res = 0;
	struct ast_frame f = { AST_FRAME_CONTROL, };
	int isoutbound;

	if (!p) {
		return -1;
	}

	ao2_ref(p, 1);


	if (!ast_test_flag(p, LOCAL_MOH_PASSTHRU) && condition == AST_CONTROL_HOLD) {
		ast_moh_start(ast, data, NULL);
	} else if (!ast_test_flag(p, LOCAL_MOH_PASSTHRU) && condition == AST_CONTROL_UNHOLD) {
		ast_moh_stop(ast);
	} else if (condition == AST_CONTROL_CONNECTED_LINE || condition == AST_CONTROL_REDIRECTING) {
		struct ast_channel *this_channel;
		struct ast_channel *the_other_channel;


		ao2_lock(p);
		isoutbound = IS_OUTBOUND(ast, p);
		if (isoutbound) {
			this_channel = p->chan;
			the_other_channel = p->owner;
		} else {
			this_channel = p->owner;
			the_other_channel = p->chan;
		}
		if (the_other_channel) {
			unsigned char frame_data[1024];
			if (condition == AST_CONTROL_CONNECTED_LINE) {
				if (isoutbound) {
					ast_connected_line_copy_to_caller(ast_channel_caller(the_other_channel), ast_channel_connected(this_channel));
				}
				f.datalen = ast_connected_line_build_data(frame_data, sizeof(frame_data), ast_channel_connected(this_channel), NULL);
			} else {
				f.datalen = ast_redirecting_build_data(frame_data, sizeof(frame_data), ast_channel_redirecting(this_channel), NULL);
			}
			f.subclass.integer = condition;
			f.data.ptr = frame_data;
			res = local_queue_frame(p, isoutbound, &f, ast, 1);
		}
		ao2_unlock(p);
	} else {

		ao2_lock(p);


		if (0 <= condition || ast_test_flag(p, LOCAL_NO_OPTIMIZATION)) {
			isoutbound = IS_OUTBOUND(ast, p);
			f.subclass.integer = condition;
			f.data.ptr = (void *) data;
			f.datalen = datalen;
			res = local_queue_frame(p, isoutbound, &f, ast, 1);

			if (!res && (condition == AST_CONTROL_T38_PARAMETERS) &&
			    (datalen == sizeof(struct ast_control_t38_parameters))) {
				const struct ast_control_t38_parameters *parameters = data;

				if (parameters->request_response == AST_T38_REQUEST_PARMS) {
					res = AST_T38_REQUEST_PARMS;
				}
			}
		} else {
			ast_debug(4, "Blocked indication %d\n", condition);
		}
		ao2_unlock(p);
	}

	ao2_ref(p, -1);
	return res;
}
