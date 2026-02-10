Set(const int index, const bool value)
{
	if (value){
		Data[(index>>3)] |= (1 << (index&7));
	} else {
		unsigned char mask = 0xFF;
		mask ^= (1 << (index&7));
		Data[(index>>3)] &= mask;
	}
}
