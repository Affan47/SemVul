SetParameter (char *parameter, char *value)
{
  if (this->Parameters)
    {
    delete [] this->Parameters;
    }


  this->Parameters = new char [strlen (parameter) +
                              strlen (value) +
                              7];

  sprintf (this->Parameters, " \"%s\" [%s]", parameter, value);
  this->Modified ();
}
