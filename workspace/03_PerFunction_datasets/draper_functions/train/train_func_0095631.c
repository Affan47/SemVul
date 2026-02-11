snapVtx(const Vector &mouse, const Matrix &m,
			   Vector &pos, double &bound) const
{

  for (uint i = 0; i < iCP.size(); ++i)
    snapVertex(mouse, m * iCP[i], pos, bound);
}
