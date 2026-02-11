SetMinimumLevel(int minLevels)
{
  if (minLevels < 1)
    {
    minLevels = 1;
    }

  if (this->MinimumLevel == minLevels)
    {
    return;
    }

  this->Modified();
  this->MinimumLevel = minLevels;
  assert("post: is_set" && this->GetMinimumLevel()==minLevels);
}
