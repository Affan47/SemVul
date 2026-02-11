SearchRegionForDuplicate(float *point, int *pointsSoFar,
                                        int len, float tolerance2)
{
  int duplicateFound = -1;
  int id;

  for (id=0; id < len; id++)
    {
    int otherId = pointsSoFar[id];

    float *otherPoint = this->LocatorPoints + (otherId * 3);

    float distance2 = vtkMath::Distance2BetweenPoints(point, otherPoint);

    if (distance2 <= tolerance2)
      {
      duplicateFound = otherId;
      break;
      }
    }
  return duplicateFound;
}
