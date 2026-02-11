ComputeHouses(housesystem)
int housesystem;
{
  byte sz[cchSzDef];

  if (RAbs(AA) > RFromD(rDegQuad-rAxis) && housesystem < 2) {
    sprintf(sz,
      "The %s system of houses is not defined at extreme latitudes.",
      szSystem[housesystem]);
    PrintWarning(sz);
    AA = RSgn2(AA)*RFromD(rDegQuad-rAxis);
  }


  if (MinDifference(is.MC, is.Asc) < 0.0 && housesystem == 13)
    is.Asc = Mod(is.Asc + rDegHalf);

  switch (housesystem) {
  case  1: HouseKoch();           break;
  case  2: HouseEqual();          break;
  case  3: HouseCampanus();       break;
  case  4: HouseMeridian();       break;
  case  5: HouseRegiomontanus();  break;
  case  6: HousePorphyry();       break;
  case  7: HouseMorinus();        break;
  case  8: HouseTopocentric();    break;
  case  9: HouseAlcabitius();     break;
  case 10: HouseEqualMidheaven(); break;
  case 11: HousePorphyryNeo();    break;
  case 12: HouseWhole();          break;
  case 13: HouseVedic();          break;
  case 14: HouseNull();           break;
  default: HousePlacidus();
  }
}
