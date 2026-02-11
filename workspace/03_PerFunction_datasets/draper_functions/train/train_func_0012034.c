opaqueable_rubband(Rubberband* rub) {
  ClassId id = rub->GetClassId();
  return
    id == SLIDINGLINE ||
    id == SLIDINGLINELIST ||
    id == SLIDINGRECT ||
    id == SCALINGLINE ||
    id == SCALINGLINELIST ||
    id == SCALINGRECT ||
    id == RUBBERRECT ||
    id == ROTATINGLINE ||
    id == ROTATINGLINELIST ||
    id == ROTATINGRECT;
    ;
}
