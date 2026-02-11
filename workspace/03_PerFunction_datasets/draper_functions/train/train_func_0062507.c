rotate (const HepAxisAngle & ax ) {
  return rotate( ax.getAxis(), ax.delta() );
}
