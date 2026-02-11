Send(int location)
    {
      switch(this->Size)
        {
        case 1:
          vtkgl::Uniform1iv(location,this->ArraySize,this->Values);
          break;
        case 2:
          vtkgl::Uniform2iv(location,this->ArraySize,this->Values);
          break;
        case 3:
          vtkgl::Uniform3iv(location,this->ArraySize,this->Values);
          break;
        case 4:
          vtkgl::Uniform4iv(location,this->ArraySize,this->Values);
          break;
        }
    }
