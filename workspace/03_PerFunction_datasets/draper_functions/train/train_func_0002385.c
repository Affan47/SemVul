Has2D(bool Not3D)
  {
    bool hasX,hasY;
    OBAtom *atom;
    vector<OBAtom*>::iterator i;

    hasX = hasY = false;
    for (atom = BeginAtom(i);atom;atom = NextAtom(i))
      {
        if (!hasX && !IsNearZero(atom->x()))
          hasX = true;
        if (!hasY && !IsNearZero(atom->y()))
          hasY = true;
        if(Not3D && atom->z())
          return false;
      }
    if (hasX || hasY)
      return(true);
    return(false);
  }
