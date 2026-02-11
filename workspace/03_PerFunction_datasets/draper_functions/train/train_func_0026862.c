maxSonarReadDistance(maxSonarSensor_t type, uint32_t *accuracy)
{
  switch(type) {
    case MAXSONAR_MB1040_AN: {
      return maxSonarReadDistanceMB1040AN(MAXSONAR_DECK_GPIO, accuracy);
    }
  }

  maxSonarDistance = 0;
  maxSonarAccuracy = 0;
  if(accuracy) {
    *accuracy = maxSonarAccuracy;
  }

  return(maxSonarDistance);
}
