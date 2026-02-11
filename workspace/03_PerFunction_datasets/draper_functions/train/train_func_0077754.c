store_boost(struct chan_oss_pvt *o, const char *s)
{
	double boost = 0;
	if (sscanf(s, "%30lf", &boost) != 1) {
		ast_log(LOG_WARNING, "invalid boost <%s>\n", s);
		return;
	}
	if (boost < -BOOST_MAX) {
		ast_log(LOG_WARNING, "boost %s too small, using %d\n", s, -BOOST_MAX);
		boost = -BOOST_MAX;
	} else if (boost > BOOST_MAX) {
		ast_log(LOG_WARNING, "boost %s too large, using %d\n", s, BOOST_MAX);
		boost = BOOST_MAX;
	}
	boost = exp(log(10) * boost / 20) * BOOST_SCALE;
	o->boost = boost;
	ast_log(LOG_WARNING, "setting boost %s to %d\n", s, o->boost);
}
