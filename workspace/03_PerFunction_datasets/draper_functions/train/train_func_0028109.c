unpack<CRotThermParticle::exchangeType>(CRotThermParticle::exchangeType& p)
{
  const int numDoubles = 21 ;
  double db[numDoubles];

  pop_doubles(db, numDoubles);
  p.m_pos        = Vec3(db[0],db[1],db[2]);
  p.m_initPos    = Vec3(db[3],db[4],db[5]);
  p.m_vel        = Vec3(db[6],db[7],db[8]);
  p.m_angVel     = Vec3(db[9],db[10],db[11]);
  p.m_angVel_t     = Vec3(db[12],db[13],db[14]);
  p.m_quat       = Quaternion(db[15],Vec3(db[16],db[17],db[18]));
  p.m_temperature = db[19] ;
  p.m_temperature_ini = db[20] ;
}
