operator=(const Vector& v)
{
	if (length() != v.length()) {
		throw SYLV_MES_EXCEPTION("Wrong lengths for vector operator =.");
	}
	Vector::operator=(v);
	return *this;
}
