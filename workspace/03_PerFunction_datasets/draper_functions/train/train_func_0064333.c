log2fast(uint v) {
		uint c = 0;
		register uint t, tt;

		if ((tt = v >> 16))
			c = (t = v >> 24) ? 24 + LogTable256[t] : 16 + LogTable256[tt & 0xFF];
		else
			c = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
		return c;
	}
