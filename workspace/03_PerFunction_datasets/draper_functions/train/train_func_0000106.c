AdjustSpacingAndOrigin (int dimensions[3], double spacing[3],
  double origin[3])
{
  for (int i = 0; i < 3; i++)
    {
    if (spacing[i] < 0)
      {
      origin[i] = origin[i] + spacing[i] * dimensions[i];
      spacing[i] = -spacing[i];
      }
    }
  vtkDebugMacro("Adjusted Spacing " << spacing[0] << ", " << spacing[1] << ", " << spacing[2]);
  vtkDebugMacro("Adjusted origin " << origin[0] << ", " << origin[1] << ", " << origin[2]);
}
