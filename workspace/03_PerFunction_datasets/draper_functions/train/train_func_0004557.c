SetRequestInformationMethod(
  void (*f)(void *))
{
  if ( f != this->RequestInformationMethod )
    {
    this->RequestInformationMethod = f;
    this->Modified();
    }
}
