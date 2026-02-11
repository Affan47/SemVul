print_frmival(const struct v4l2_frmivalenum &frmival, const char *prefix)
{
	printf("%s\tInterval: %s ", prefix, frmtype2s(frmival.type).c_str());
	if (frmival.type == V4L2_FRMIVAL_TYPE_DISCRETE) {
		printf("%ss (%s fps)\n", fract2sec(frmival.discrete).c_str(),
				fract2fps(frmival.discrete).c_str());
	} else if (frmival.type == V4L2_FRMIVAL_TYPE_STEPWISE) {
		printf("%ss - %ss with step %ss (%s-%s fps)\n",
				fract2sec(frmival.stepwise.min).c_str(),
				fract2sec(frmival.stepwise.max).c_str(),
				fract2sec(frmival.stepwise.step).c_str(),
				fract2fps(frmival.stepwise.max).c_str(),
				fract2fps(frmival.stepwise.min).c_str());
	}
}
