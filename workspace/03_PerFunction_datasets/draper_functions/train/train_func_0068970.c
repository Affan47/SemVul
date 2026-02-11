orientation(Orientation orientation_)
{
  if (_orientation!=orientation_)
   {
     _orientation=orientation_;
     if (orientation()==Horizontal)
      {
        if (tabAlignment()==MSTop||tabAlignment()==MSBottom) _tabAlignment=MSRight;
	upLeftArrow()->type(MSArrow::Up);
	downRightArrow()->type(MSArrow::Down);
      }
     else
      {
        if (tabAlignment()==MSLeft||tabAlignment()==MSRight) _tabAlignment=MSBottom;
	upLeftArrow()->type(MSArrow::Left);
	downRightArrow()->type(MSArrow::Right);
      }
     adjustSize();
     if (mapped()==MSTrue)
      {


	MSNodeItem *hp=childListHead();
	MSNodeItem *np=hp;
	NotebookEntry *entry;
	while ((np=np->next())!=hp)
	 {
	   entry=(NotebookEntry *)np->data();
	   if (entry->tab()->mapped()==MSTrue) entry->tab()->redraw();
	 }
      }
   }
}
