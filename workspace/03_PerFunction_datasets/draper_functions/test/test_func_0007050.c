SetComponents(int c1, int c2)
{
  int modified = 0;

  if (this->Components[0] != c1)
    {
    this->Components[0] = c1;
    modified = 1;
    }
  if (this->Components[1] != c2)
    {
    this->Components[1] = c2;
    modified = 1;
    }

  if (modified || this->NumberOfComponents != 2)
    {
    this->NumberOfComponents = 2;
    this->Modified();
    }
}
