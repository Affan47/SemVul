operator==(const vtkBalloon &balloon) const
    {
      if ( this->Image == balloon.Image )
        {
        if ( this->Text == balloon.Text )
          {
          return 1;
          }
        }
      return 0;
    }
