setRawIPString(void)
{
  unsigned char *bytes;
  bytes = (unsigned char *)inAddr();
  if (bytes != NULL)
    sprintf(myRawIPString, "%d.%d.%d.%d",
	    bytes[0], bytes[1], bytes[2], bytes[3]);
  myIPString = myRawIPString;
}
