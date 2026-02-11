startBlockingModAutoIndex(request_rec *r) {
		RequestNote *note = getRequestNote(r);
		if (note != 0 && hasModAutoIndex()) {
			note->handlerBeforeModAutoIndex = r->handler;
			r->handler = "";
		}
		return DECLINED;
	}
