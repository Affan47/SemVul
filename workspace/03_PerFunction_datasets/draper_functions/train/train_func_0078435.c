clone() const
{
	MathMacro * copy = new MathMacro(*this);
	copy->needsUpdate_ = true;

	return copy;
}
