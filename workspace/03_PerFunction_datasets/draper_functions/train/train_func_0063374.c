AMF_EncodeArray(AMFObject *obj, char *pBuffer, char *pBufEnd)
{
  int i;

  if (pBuffer+4 >= pBufEnd)
    return NULL;

  *pBuffer++ = AMF_STRICT_ARRAY;

  pBuffer = AMF_EncodeInt32(pBuffer, pBufEnd, obj->o_num);

  for (i = 0; i < obj->o_num; i++)
    {
      char *res = AMFProp_Encode(&obj->o_props[i], pBuffer, pBufEnd);
      if (res == NULL)
	{
	  RTMP_Log(RTMP_LOGERROR, "AMF_Encode - failed to encode property in index %d",
	      i);
	  break;
	}
      else
	{
	  pBuffer = res;
	}
    }


  return pBuffer;
}
