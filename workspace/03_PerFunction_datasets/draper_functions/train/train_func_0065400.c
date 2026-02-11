strcasequotecmp(const std::string &inStr1,
                                     const std::string &inStr2)
{
std::string str1 = inStr1;
std::string str2 = inStr2;

	int x = 0;
	while (x < str1.length()) {
		if (isalpha(str1[x]) && isupper(str1[x]))
			str1[x] = tolower(str1[x]);
	x++;
	}

	x = 0;
	while (x < str2.length()) {
		if (isalpha(str2[x]) && isupper(str2[x]))
			str2[x] = tolower(str2[x]);
	x++;
	}

  int len1 = str1.length();
  size_t pos1 = 0;
  if ((len1 >= 2) && (str1[0] == '\"') && (str1[len1 - 1] == '\"')) {
    pos1 = 1;
  }
  int len2 = str2.length();
  size_t pos2 = 0;
  if ((len2 >= 2) && (str2[0] == '\"') && (str2[len2 - 1] == '\"')) {
    pos2 = 1;
  }


#if defined(__GNUC__) && (__GNUC__ <= 2) && (__GNUC_MINOR__ <= 96)
#warning Using GCC 2.96 or less so must use nonstandard std::string::compare method.
  int cmp = str1.compare(str2.substr(pos2, len2 - 2 * pos2), pos1, len1 - 2 * pos1);
#else
  int cmp = str1.compare(pos1,
	 	  	 len1 - 2 * pos1,
                         str2,
                         pos2,
			 len2 - 2 * pos2);
#endif

  return cmp;

}
