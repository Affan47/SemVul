setVel( const Vector2D &newVel ) {
  Vector2D temp = vel;
  vel = newVel;
  if ( vel.getLength() >= getActVelMax() ) {
    vel.setLength(getActVelMax());
  }
  return temp;
}
