GuessFromModality(const char *modality, unsigned int dim )
{

  if( !modality || !dim ) return;

  int i = 0;
  while( MSModalityTypes[i].Modality &&
    (strcmp(modality, MSModalityTypes[i].Modality) != 0
     || MSModalityTypes[i].Retired
     || MSModalityTypes[i].Dimension < dim ))
    {
    ++i;
    }
  if( MSModalityTypes[i].Modality )
    {

    MSField = (MSType)i;
    }
}
