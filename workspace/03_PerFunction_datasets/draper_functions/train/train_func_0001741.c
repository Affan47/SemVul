loadA(Action* a) {
  for (int i = 0; i < numPreconds(a); i++)
    playground[getPrecond(a,i)] |= FL_PRE;

  for (int i = 0; i < numAdds(a); i++)
    playground[getAdd(a,i)] |= FL_ADD;

  for (int i = 0; i < numDels(a); i++)
    playground[getDel(a,i)] |= FL_DEL;
}
