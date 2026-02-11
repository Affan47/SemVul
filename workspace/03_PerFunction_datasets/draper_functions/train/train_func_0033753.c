ReadLine(char result[256])
{
  this->IS->getline(result,256);

  if (this->IS->fail())
      {


      this->IS->clear();
      return 0;
      }

  return 1;
}
