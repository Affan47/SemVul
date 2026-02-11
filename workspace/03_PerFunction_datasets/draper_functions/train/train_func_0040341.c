addmag(int s, const N a, const N b, N c)
{
     if (abscmp(a, b) > 0) addmag0(1, a, b, c); else addmag0(s, b, a, c);
}
