div(std::string const& a, std::string& b)
{
#ifdef DEBUG
  std::cerr << "Entering vnl_decnum::div with " << a << " and " << b << '\n';
#endif
  int na=int(a.length()), nb=int(b.length());
  assert(na >= nb);
  if (comp(a,b)) ++nb;
  std::string u = "1";
  while (nb<na) { b.push_back('0'), u.push_back('0'); ++nb; }
  std::string c = b;
  for (; u[0]<'9'; u[0]++) {
    vnl_decnum d = plus(c,b,0L);
    if (vnl_decnum(a) < d) { b=c; return u; }
    c=d.data();
  }

  b=c; return u;
}
