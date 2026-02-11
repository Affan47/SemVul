check_range(enum v4l2_ctrl_type type,
		s64 min, s64 max, u64 step, s64 def)
{
	switch (type) {
	case V4L2_CTRL_TYPE_BOOLEAN:
		if (step != 1 || max > 1 || min < 0)
			return -ERANGE;

	case V4L2_CTRL_TYPE_U8:
	case V4L2_CTRL_TYPE_U16:
	case V4L2_CTRL_TYPE_U32:
	case V4L2_CTRL_TYPE_INTEGER:
	case V4L2_CTRL_TYPE_INTEGER64:
		if (step == 0 || min > max || def < min || def > max)
			return -ERANGE;
		return 0;
	case V4L2_CTRL_TYPE_BITMASK:
		if (step || min || !max || (def & ~max))
			return -ERANGE;
		return 0;
	case V4L2_CTRL_TYPE_MENU:
	case V4L2_CTRL_TYPE_INTEGER_MENU:
		if (min > max || def < min || def > max)
			return -ERANGE;


		if (step && ((1 << def) & step))
			return -EINVAL;
		return 0;
	case V4L2_CTRL_TYPE_STRING:
		if (min > max || min < 0 || step < 1 || def)
			return -ERANGE;
		return 0;
	default:
		return 0;
	}
}
