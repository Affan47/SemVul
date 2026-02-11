falloc(q, n, s)
voidpf q;
uInt n;
uInt s;
{
  Assert(s == sizeof(inflate_huft) && n <= fixed_left,
         "inflate_trees falloc overflow");
  if (q) s++;
  fixed_left -= n;
  return (voidpf)(fixed_mem + fixed_left);
}
