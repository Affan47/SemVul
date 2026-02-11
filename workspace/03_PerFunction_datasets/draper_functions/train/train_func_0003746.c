SetValues(float *values)
    {
      int i=0;
      while(i<this->Rows)
        {
        int j=0;
        while(j<this->Columns)
          {
          int index=i*this->Columns+j;
          this->Values[index]=values[index];
          ++j;
          }
        ++i;
        }
    }
