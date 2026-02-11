getShortRank ()
{
  if (ranking == 0) return "AB";
  else if (ranking == 1) return "ARM";
  else if (ranking == 2) return "A1C";
  else if (ranking == 3) return "2ND LT";
  else if (ranking == 4) return "1ST LT";
  else if (ranking == 5) return "CAPT";
  else if (ranking == 6) return "MAJ";
  else if (ranking == 7) return "COL";
  else return "GEN";
}
