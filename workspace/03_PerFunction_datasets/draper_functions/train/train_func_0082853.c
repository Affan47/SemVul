RS_BlendID (char *blend)
{
	if (!blend[0])
		return 0;
	if (!Q_strcasecmp (blend, "GL_ZERO"))
		return GL_ZERO;
	if (!Q_strcasecmp (blend, "GL_ONE"))
		return GL_ONE;
	if (!Q_strcasecmp (blend, "GL_DST_COLOR"))
		return GL_DST_COLOR;
	if (!Q_strcasecmp (blend, "GL_ONE_MINUS_DST_COLOR"))
		return GL_ONE_MINUS_DST_COLOR;
	if (!Q_strcasecmp (blend, "GL_SRC_ALPHA"))
		return GL_SRC_ALPHA;
	if (!Q_strcasecmp (blend, "GL_ONE_MINUS_SRC_ALPHA"))
		return GL_ONE_MINUS_SRC_ALPHA;
	if (!Q_strcasecmp (blend, "GL_DST_ALPHA"))
		return GL_DST_ALPHA;
	if (!Q_strcasecmp (blend, "GL_ONE_MINUS_DST_ALPHA"))
		return GL_ONE_MINUS_DST_ALPHA;
	if (!Q_strcasecmp (blend, "GL_SRC_ALPHA_SATURATE"))
		return GL_SRC_ALPHA_SATURATE;
	if (!Q_strcasecmp (blend, "GL_SRC_COLOR"))
		return GL_SRC_COLOR;
	if (!Q_strcasecmp (blend, "GL_ONE_MINUS_SRC_COLOR"))
		return GL_ONE_MINUS_SRC_COLOR;

	return 0;
}
