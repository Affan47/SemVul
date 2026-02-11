typhoon_process_response(struct typhoon *tp, int resp_size,
				struct resp_desc *resp_save)
{
	struct typhoon_indexes *indexes = tp->indexes;
	struct resp_desc *resp;
	u8 *base = tp->respRing.ringBase;
	int count, len, wrap_len;
	u32 cleared;
	u32 ready;

	cleared = le32_to_cpu(indexes->respCleared);
	ready = le32_to_cpu(indexes->respReady);
	while(cleared != ready) {
		resp = (struct resp_desc *)(base + cleared);
		count = resp->numDesc + 1;
		if(resp_save && resp->seqNo) {
			if(count > resp_size) {
				resp_save->flags = TYPHOON_RESP_ERROR;
				goto cleanup;
			}

			wrap_len = 0;
			len = count * sizeof(*resp);
			if(unlikely(cleared + len > RESPONSE_RING_SIZE)) {
				wrap_len = cleared + len - RESPONSE_RING_SIZE;
				len = RESPONSE_RING_SIZE - cleared;
			}

			memcpy(resp_save, resp, len);
			if(unlikely(wrap_len)) {
				resp_save += len / sizeof(*resp);
				memcpy(resp_save, base, wrap_len);
			}

			resp_save = NULL;
		} else if(resp->cmd == TYPHOON_CMD_READ_MEDIA_STATUS) {
			typhoon_media_status(tp->dev, resp);
		} else if(resp->cmd == TYPHOON_CMD_HELLO_RESP) {
			typhoon_hello(tp);
		} else {
			netdev_err(tp->dev,
				   "dumping unexpected response 0x%04x:%d:0x%02x:0x%04x:%08x:%08x\n",
				   le16_to_cpu(resp->cmd),
				   resp->numDesc, resp->flags,
				   le16_to_cpu(resp->parm1),
				   le32_to_cpu(resp->parm2),
				   le32_to_cpu(resp->parm3));
		}

cleanup:
		typhoon_inc_resp_index(&cleared, count);
	}

	indexes->respCleared = cpu_to_le32(cleared);
	wmb();
	return resp_save == NULL;
}
