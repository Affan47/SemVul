emitRoundModeI(RoundMode rnd, const int pos)
{
   uint8_t n;

   switch (rnd) {
   case ROUND_MI: n = 1; break;
   case ROUND_PI: n = 2; break;
   case ROUND_ZI: n = 3; break;
   default:
      n = 0;
      assert(rnd == ROUND_NI);
      break;
   }
   code[pos / 32] |= n << (pos % 32);
}
