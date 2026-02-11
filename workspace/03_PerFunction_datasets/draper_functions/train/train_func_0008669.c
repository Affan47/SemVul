comp_t_2_double(comp_t c_num)
{
  unsigned long in = 0;


  in = c_num & 017777;
  c_num >>= 13;

  while (c_num)
    {
      c_num--;
      in <<= 3;
    }


  return (double) in;
}
