integerState(void) const
{
  MSIntVector vector;
  MSNodeItem *hp=(MSNodeItem *)childListHead();
  MSNodeItem *np=hp;

  while ((np=np->next())!=hp)
   {
     MSLayoutEntry *entry=(MSLayoutEntry *)np->data();
     MSActionButton *button=(MSActionButton *)entry->widget();
     if (button->state()==MSTrue) vector.append(button->integerTag());
   }
  return vector;
}
