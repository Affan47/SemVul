alignSeptet()
{
  while (((_op - _septetStart) * 8 + _bi) % 7 != 0) setBit();
}
