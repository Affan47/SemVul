get_string (const ustring& format) const throw ()
{
	switch (qualifier)
	{
	case Q_UNK: return _("(unknown)");
	case Q_NA: return _("(n/a)");

	case Q_EST: return compose::ucompose (_("(%1)"), do_get_string (format));

	case Q_CA: return compose::ucompose (_("~%1"), do_get_string (format));

	case Q_ISO: return compose::ucompose (_("[%1]"), do_get_string (format));
	case Q_NEUTRAL:
	default:
		return do_get_string (format);
	}
}
