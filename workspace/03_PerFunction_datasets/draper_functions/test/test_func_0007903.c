ast_bridge_handle_trip(struct ast_bridge *bridge, struct ast_bridge_channel *bridge_channel, struct ast_channel *chan, int outfd)
{

	if (chan && !bridge_channel) {
		bridge_channel = find_bridge_channel(bridge, chan);
	}


	if (chan && bridge_channel) {
		struct ast_frame *frame = (((bridge->features.mute) || (bridge_channel->features && bridge_channel->features->mute)) ? ast_read_noaudio(chan) : ast_read(chan));


		if (!frame || (frame->frametype == AST_FRAME_CONTROL && frame->subclass.integer == AST_CONTROL_HANGUP)) {

			ast_bridge_change_state(bridge_channel, AST_BRIDGE_CHANNEL_STATE_END);
		} else if (frame->frametype == AST_FRAME_CONTROL && bridge_drop_control_frame(frame->subclass.integer)) {
			ast_debug(1, "Dropping control frame from bridge channel %p\n", bridge_channel);
		} else if (frame->frametype == AST_FRAME_DTMF_BEGIN || frame->frametype == AST_FRAME_DTMF_END) {
			int dtmf_passthrough = bridge_channel->features ?
				bridge_channel->features->dtmf_passthrough :
				bridge->features.dtmf_passthrough;

			if (frame->frametype == AST_FRAME_DTMF_BEGIN) {
				frame = bridge_handle_dtmf(bridge, bridge_channel, frame);
			}

			if (frame && dtmf_passthrough) {
				bridge->technology->write(bridge, bridge_channel, frame);
			}
		} else {

			bridge->technology->write(bridge, bridge_channel, frame);
		}

		if (frame) {
			ast_frfree(frame);
		}
		return;
	}


	if (outfd > -1 && bridge->technology->fd) {
		bridge->technology->fd(bridge, bridge_channel, outfd);
		return;
	}


	if (bridge->technology->poke && bridge_channel) {
		bridge->technology->poke(bridge, bridge_channel);
		return;
	}

	return;
}
