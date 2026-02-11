DtsGetMaxYUVSize(DTS_LIB_CONTEXT *Ctx, uint32_t *YbSz, uint32_t *UVbSz)
{
	if (Ctx->b422Mode) {
		*YbSz = (1920*1090)*2;
		*UVbSz = 0;
	} else {
		*YbSz  = 1920*1090;
		*UVbSz = 1920*1090/2;
	}
}
