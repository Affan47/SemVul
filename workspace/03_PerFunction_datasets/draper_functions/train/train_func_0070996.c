openConstraints()
{
  int i;
  char filename[PATH_MAX];

  for(i = 0; i < constraintFiles; ++i)
    {

      manager->openStream(constraintFileStream[i], extension[i], std::ios::in);
    }

  fstream& str = constraintFileStream[HEADER];
  str >> constraintCount;
  return 0;
}
