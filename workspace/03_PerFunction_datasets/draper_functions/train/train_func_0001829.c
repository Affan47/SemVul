italic_angle() const
{
    if (_override_italic_angle)
	return _italic_angle;
    else if (cff) {
	double d;
	(void) cff->dict_value(Efont::Cff::oItalicAngle, &d);
	return d;
    } else
	return post->italic_angle();
}
