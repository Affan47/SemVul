sniff (const UT_ByteBuf * pBB, const char * xml_type)
{
  UT_ASSERT (pBB);
  UT_ASSERT (xml_type);

  if ((pBB == 0) || (xml_type == 0)) return false;

  const char * buffer = reinterpret_cast<const char *>(pBB->getPointer (0));
  UT_uint32 length = pBB->getLength ();

  return sniff (buffer, length, xml_type);
}
