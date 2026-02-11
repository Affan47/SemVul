Get(byte &outByte)
{
	if (AttachedTransformation())
		return AttachedTransformation()->Get(outByte);
	else
		return Get(&outByte, 1);
}
