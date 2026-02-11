getVal64(unsigned id)
{
	const v4l2_queryctrl &qctrl = m_ctrlMap[id];
	QWidget *w = m_widgetMap[qctrl.id];
	long long v = 0;

	switch (qctrl.type) {
	case V4L2_CTRL_TYPE_INTEGER64:
		v = static_cast<QLineEdit *>(w)->text().toLongLong();
		break;
	default:
		break;
	}
	setWhat(w, id, v);
	return v;
}
