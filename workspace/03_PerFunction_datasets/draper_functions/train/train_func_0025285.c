vtkCCSPolyInPoly(
  const vtkCCSPoly &outerPoly, const vtkCCSPoly &innerPoly,
  vtkPoints *points, const double normal[3],
  const double *pp, const double bounds[6],
  double tol2)
{


  size_t n = outerPoly.size();
  size_t m = innerPoly.size();

  for (size_t jj = 0; jj < m; jj++)
    {

    size_t kk = (jj>>1) + (jj&1)*((m+1)>>1);
    double p[3];
    points->GetPoint(innerPoly[kk], p);

    if (vtkPolygon::PointInPolygon(
        p, static_cast<int>(n), const_cast<double *>(pp),
        const_cast<double *>(bounds), const_cast<double *>(normal)))
      {
      int pointOnEdge = 0;
      double q1[3], q2[3];
      points->GetPoint(outerPoly[n-1], q1);

      for (size_t ii = 0; ii < n; ii++)
        {
        points->GetPoint(outerPoly[ii], q2);
        double t, dummy[3];

        if (vtkLine::DistanceToLine(p, q1, q2, t, dummy) < tol2)
          {
          pointOnEdge = 1;
          break;
          }
        q1[0] = q2[0]; q1[1] = q2[1]; q1[2] = q2[2];
        }

      if (!pointOnEdge)
        {

        return 1;
        }
      }
    }


  return 0;
}
