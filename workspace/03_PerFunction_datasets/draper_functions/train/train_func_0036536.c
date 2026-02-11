vtkOpaqueAtVertices (int XSize, int YSize, double ScaleFactor,
                          vtkUnsignedCharArray *newScalars)
{
  int i, j;
  double opacity;
  double point[3];
  double XScale = XSize + 1.0;
  double YScale = YSize + 1.0;
  unsigned char AGrayValue[2];
  double dist, distToV2, distToV3;
  double v1[3] = {0.0, 0.0, 0.0};
  double v2[3] = {1.0, 0.0, 0.0};
  double v3[3] = {0.5, sqrt(3.0)/2.0, 0.0};

  point[2] = 0.0;
  AGrayValue[0] = AGrayValue[1] = 255;

  for (j = 0; j < YSize; j++)
    {
    for (i = 0; i < XSize; i++)
      {
      point[0] = i / XScale;
      point[1] = j / YScale;
      dist = vtkMath::Distance2BetweenPoints (point, v1);
      distToV2 = vtkMath::Distance2BetweenPoints (point, v2);
      if (distToV2 < dist)
        {
        dist = distToV2;
        }
      distToV3 = vtkMath::Distance2BetweenPoints (point, v3);
      if (distToV3 < dist)
        {
        dist = distToV3;
        }

      opacity = sqrt(dist) * ScaleFactor;
      if (opacity < .5)
        {
        opacity = 0.0;
        }
      if (opacity > .5)
        {
        opacity = 1.0;
        }
      opacity = 1.0 - opacity;
      AGrayValue[1] = static_cast<unsigned char>(opacity * 255);
      newScalars->SetValue ((XSize*j + i)*2, AGrayValue[0]);
      newScalars->SetValue ((XSize*j + i)*2 + 1, AGrayValue[1]);
      }
    }
}
