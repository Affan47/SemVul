syntaxIsValid(const char* sior)
{

  int i;
  for (i=4; sior[i]; i++) {
    if (!((sior[i] >= '0' && sior[i] <= '9') ||
	  (sior[i] >= 'a' && sior[i] <= 'f') ||
	  (sior[i] >= 'A' && sior[i] <= 'F')))
      return 0;
  }
  if (i == 4 || i % 2) {

    return 0;
  }
  return 1;
}
