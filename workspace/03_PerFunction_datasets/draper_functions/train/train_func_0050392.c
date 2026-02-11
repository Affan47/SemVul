obstacle (CRect &rect, int z)
{
  CDRGrid::iterator  coord;
               long  x, y, X, Y;


  if ( !z || (z >= _drgrid->Z) ) return;

  coord = _drgrid->origin;

  X = (_drgrid->X <= rect.x2) ? _drgrid->X - 1 : rect.x2;
  Y = (_drgrid->Y <= rect.y2) ? _drgrid->Y - 1 : rect.y2;

  x =  (rect.x1>0) ? rect.x1 : 0;
  for ( ; x <= X; x++) {
    y =  (rect.y1>0) ? rect.y1 : 0;
    for ( ; y <= Y; y++) {
      if ( ! (*this)[ coord.set (x, y, z) ].terminal () ) {

        (*this)[ coord ].data.obstacle = true;
      }
    }
  }
}
