getValue() const
{
	if (! this->value->isEnabled()) return QString();

	return this->value->text();
}
