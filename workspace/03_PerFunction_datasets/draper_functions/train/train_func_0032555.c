BuildPropHitList(unsigned char* pixelbuffer)
{
  for (int yy=0; yy <= static_cast<int>(this->Area[3]-this->Area[1]); yy++)
    {
    for (int xx=0; xx <= static_cast<int>(this->Area[2]-this->Area[0]); xx++)
      {
      int val = this->Convert(xx, yy, pixelbuffer);
      if (val > 0)
        {
        val--;
        if (this->Internals->HitProps.find(val) ==
          this->Internals->HitProps.end())
          {
          this->Internals->HitProps.insert(val);
          }
        }
      }
    }
}
