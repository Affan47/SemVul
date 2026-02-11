EncodePoint(BufferedTransformation &bt, const Point &P, bool compressed) const
{
	if (P.identity)
		NullStore().TransferTo(bt, EncodedPointSize(compressed));
	else if (compressed)
	{
		bt.Put(2 + (!P.x ? 0 : m_field->Divide(P.y, P.x).GetBit(0)));
		P.x.Encode(bt, m_field->MaxElementByteLength());
	}
	else
	{
		unsigned int len = m_field->MaxElementByteLength();
		bt.Put(4);
		P.x.Encode(bt, len);
		P.y.Encode(bt, len);
	}
}
