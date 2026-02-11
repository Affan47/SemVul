addBond(int source, int target, int order, bool isUp, bool isDown)
    {


      if (isDown)
        upDown.push_back(IsDown);
      else if (isUp)
        upDown.push_back(IsUp);
      else
        upDown.push_back(IsNotUpDown);


      mol->AddBond(indices[source], indices[target], order);
      if (order == 5)
        mol->GetBond(mol->NumBonds() - 1)->SetAromatic();
    }
