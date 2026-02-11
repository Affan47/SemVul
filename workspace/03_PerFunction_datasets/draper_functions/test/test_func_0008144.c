AllocateArrays(int num)
{
  int i;

  if ( num < 0 )
    {
    num = 0;
    }

  if ( num == this->NumberOfArrays )
    {
    return;
    }
  else
    {
    this->Modified();
    }

  if ( num == 0 )
    {
    this->Initialize();
    }
  else if ( num < this->NumberOfArrays )
    {
    for ( i=num; i < this->NumberOfArrays; i++)
      {
      if( this->Data[i] )
        {
        this->Data[i]->UnRegister(this);
        }
      }
    this->NumberOfArrays = num;
    }
  else
    {
    vtkAbstractArray **data=new vtkAbstractArray* [num];

    for ( i=0; i < this->NumberOfArrays; i++ )
      {
      data[i] = this->Data[i];
      }


    for ( i=this->NumberOfArrays; i < num; i++ )
      {
      data[i] = 0;
      }


    delete [] this->Data;


    this->Data = data;
    this->NumberOfArrays = num;
    }
}
