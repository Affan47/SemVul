feistel(char *codeString, char *roundKey,
	     int msgLen, int keyLen)
{
  int i, c, mod;
  char tempKey[keyLen];
  for (i = 0; i < keyLen; i++)
    tempKey[i] = roundKey[i];

  for (i = 0; i < msgLen; i++) {
    mod = hash(tempKey, keyLen);
    c = (int) codeString[i];
    mod %= c + 5;
    mod &= CHAR_MAX;

    rotateKey(tempKey, codeString[i], keyLen);

    codeString[i] = mod;
  }
}
