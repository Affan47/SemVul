Clear()
    {
      vtkIdType i=0;
      vtkIdType c=this->Vector.size();
      while(i<c)
        {
        if(this->Vector[i]!=0)
          {
          while(!this->Vector[i]->empty())
            {
            (*this->Vector[i]->begin())->Unref();
            this->Vector[i]->pop_front();
            }
          delete this->Vector[i];
          this->Vector[i]=0;
          }
        ++i;
        }
      while(!this->AllFaces.empty())
        {
        (*this->AllFaces.begin())->Unref();
        this->AllFaces.pop_front();
        }
    }
