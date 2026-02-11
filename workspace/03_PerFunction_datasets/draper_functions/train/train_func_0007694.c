updateActionLevel(short change_in_value)
{
  currentActionLevel += change_in_value;

  if (currentActionLevel < 0)
    currentActionLevel = 0;

  if (currentActionLevel > MAX_MESH_ACTION_LEVEL)
    currentActionLevel = MAX_MESH_ACTION_LEVEL;

  if (currentActionLevel > maxActionLevel)
    maxActionLevel = currentActionLevel;

  return currentActionLevel;
}
