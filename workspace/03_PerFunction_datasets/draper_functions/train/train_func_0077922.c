packInto(CVarMPIBuffer* B) const
{
  int sc;
  console.XDebug() << "CSoftBWallIGP::packInto( " << B << " )\n";
  CBWallIGP::packInto(B);
  B->append(m_shearK);
  if (m_scaling) {
     sc = 1;
  }
  else {
     sc = 0;
  }
  B->append(sc);
  console.XDebug() << "end CSoftBWallIGP::packInto()\n ";
}
