allWidgetsDo(MSWidgetIterator &iterator_,MSWidgetIterationType type_)
{
  if (type_==MSBreadthFirst)
   {
     MSWidgetVector vector(this);
     return (breadthFirstIteration(vector,iterator_));
   }
  else return (depthFirstIteration(iterator_));
}
