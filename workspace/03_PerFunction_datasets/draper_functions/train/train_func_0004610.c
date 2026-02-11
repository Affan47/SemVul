symbolName(String s)
{
  return (!s.empty() && (('a' <= s[0] && s[0] <= 'z') ||
			 ('A' <= s[0] && s[0] <= 'Z')));
}
