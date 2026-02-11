getCtrlFlags(unsigned flags)
{
	QString s;

	if (flags & V4L2_CTRL_FLAG_GRABBED)
		s += "grabbed ";
	if (flags & V4L2_CTRL_FLAG_READ_ONLY)
		s += "readonly ";
	if (flags & V4L2_CTRL_FLAG_UPDATE)
		s += "update ";
	if (flags & V4L2_CTRL_FLAG_INACTIVE)
		s += "inactive ";
	if (flags & V4L2_CTRL_FLAG_VOLATILE)
		s += "volatile ";
	if (flags & V4L2_CTRL_FLAG_SLIDER)
		s += "slider ";
	if (s.length()) s = QString("\nFlags: ") + s;
	return s;
}
