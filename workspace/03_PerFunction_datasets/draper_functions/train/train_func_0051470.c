getFreeTupple(vec_byte refTupple, unsigned int changeIdx)
{
  vec_byte res = refTupple;
  int rank = changeIdx - 1;
  for (uint8_t i = 0; i < 255; i++)
    {
      res[changeIdx] = i;
      map_tupple_ftnode::const_iterator tI = NodeByTupple.find(res);
      if (tI == NodeByTupple.end())
	return res;
    }
  cout << "ABORT: fail to get free tupple! (in 255 indexies)" << endl;
  abort();
}
