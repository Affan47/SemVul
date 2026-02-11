Mean() const
{
   if (Shape > 1) return Shape/(Shape-1.0);
   else return PlusInfinity;
}
