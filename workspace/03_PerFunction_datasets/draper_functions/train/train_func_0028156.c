setAttribute(s32 index, bool value)
{
	if ((u32)index < Attributes.size())
		Attributes[index]->setBool(value);
}
