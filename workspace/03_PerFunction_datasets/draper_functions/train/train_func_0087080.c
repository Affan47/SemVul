calculateDiamondValueFuel(MapField* a, MapField* b, MapField* c, MapField* d) {
  int value = static_cast<int>((a->temp3 + b->temp3 + c->temp3 + d->temp3)/4 + createRandomValue(static_cast<int>(calculateCurrentOffset(maxFuelOffset) * fuelRoughness)) * createAlgebraicSign());
  if(value > MAXFUELVALUE * (1 + additionalResourceFreeFieldsPercentageFuel / 100)) {
    value = MAXFUELVALUE * (1 + additionalResourceFreeFieldsPercentageFuel /100);
  } else if( value < MINFUELVALUE) {
    value = MINFUELVALUE;
  }
  return value;
}
