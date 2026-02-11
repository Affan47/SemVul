stun_get_message_len_str(u08bits *buf, size_t blen, int padding, size_t *app_len) {
	if (buf && blen) {

		if (buf && blen >= STUN_HEADER_LENGTH) {
			if (!STUN_VALID_CHANNEL(nswap16(((const u16bits*)buf)[0]))) {
				if ((((u08bits) buf[0]) & ((u08bits) (0xC0))) == 0) {
					if (nswap32(((const u32bits*)(buf))[1])
							== STUN_MAGIC_COOKIE) {
						u16bits len = nswap16(((const u16bits*)(buf))[1]);
						if ((len & 0x0003) == 0) {
							len += STUN_HEADER_LENGTH;
							if ((size_t) len <= blen) {
								*app_len = (size_t)len;
								return (int)len;
							}
						}
					}
				}
			}
		}


		{
			int http_len = is_http_get_inline(((char*)buf), blen);
			if((http_len>0) && ((size_t)http_len<=blen)) {
				*app_len = (size_t)http_len;
				return http_len;
			}
		}


		if(blen>=4) {
			u16bits chn=nswap16(((const u16bits*)(buf))[0]);
			if(STUN_VALID_CHANNEL(chn)) {

				u16bits bret = (4+(nswap16(((const u16bits*)(buf))[1])));

				*app_len = bret;

				if(padding && (bret & 0x0003)) {
					bret = ((bret>>2)+1)<<2;
				}

				if(bret<=blen) {
					return bret;
				}
			}
		}

	}

	return -1;
}
