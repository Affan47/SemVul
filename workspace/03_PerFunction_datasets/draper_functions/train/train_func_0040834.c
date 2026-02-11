http_Write(struct worker *w, unsigned vsl_id, const struct http *hp, int resp)
{
	unsigned u, l;

	if (resp) {
		l = WRW_WriteH(w, &hp->hd[HTTP_HDR_PROTO], " ");
		WSLH(w, vsl_id, hp, HTTP_HDR_PROTO);

		hp->hd[HTTP_HDR_STATUS].b = WS_Alloc(w->ws, 4);
		AN(hp->hd[HTTP_HDR_STATUS].b);

		sprintf(hp->hd[HTTP_HDR_STATUS].b, "%3d", hp->status);
		hp->hd[HTTP_HDR_STATUS].e = hp->hd[HTTP_HDR_STATUS].b + 3;

		l += WRW_WriteH(w, &hp->hd[HTTP_HDR_STATUS], " ");
		WSLH(w, vsl_id, hp, HTTP_HDR_STATUS);

		l += WRW_WriteH(w, &hp->hd[HTTP_HDR_RESPONSE], "\r\n");
		WSLH(w, vsl_id, hp, HTTP_HDR_RESPONSE);
	} else {
		AN(hp->hd[HTTP_HDR_URL].b);
		l = WRW_WriteH(w, &hp->hd[HTTP_HDR_REQ], " ");
		WSLH(w, vsl_id, hp, HTTP_HDR_REQ);
		l += WRW_WriteH(w, &hp->hd[HTTP_HDR_URL], " ");
		WSLH(w, vsl_id, hp, HTTP_HDR_URL);
		l += WRW_WriteH(w, &hp->hd[HTTP_HDR_PROTO], "\r\n");
		WSLH(w, vsl_id, hp, HTTP_HDR_PROTO);
	}
	for (u = HTTP_HDR_FIRST; u < hp->nhd; u++) {
		if (hp->hd[u].b == NULL)
			continue;
		AN(hp->hd[u].b);
		AN(hp->hd[u].e);
		l += WRW_WriteH(w, &hp->hd[u], "\r\n");
		WSLH(w, vsl_id, hp, u);
	}
	l += WRW_Write(w, "\r\n", -1);
	return (l);
}
