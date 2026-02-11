equals( const PhraseAlignment& other )
	{
		if (this == &other) return true;
		if (other.GetTarget() != GetTarget()) return false;
		if (other.GetSource() != GetSource()) return false;
		if (other.alignedToT != alignedToT) return false;
		if (other.alignedToS != alignedToS) return false;
		return true;
	}
