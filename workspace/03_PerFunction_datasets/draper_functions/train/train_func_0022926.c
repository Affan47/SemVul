IsDoneWithTraversal()
      {
      if (!this->DataObject)
        {
        return true;
        }

      if (this->PassSelf)
        {
        return false;
        }

      if (!this->CompositeDataSet)
        {
        return true;
        }

      if (this->Reverse &&
        this->ReverseIter == this->GetInternals(this->CompositeDataSet)->Children.rend())
        {
        return true;
        }

      if (!this->Reverse &&
        this->Iter == this->GetInternals(this->CompositeDataSet)->Children.end())
        {
        return true;
        }
      return false;
      }
