CorrectFormalCharges(OBMol *mol)
  {
    if (!mol)
      return;


    FOR_ATOMS_OF_MOL(atom, *mol) {

      if ((atom->GetAtomicNum() == 7 || atom->GetAtomicNum() == 15)
          && atom->BOSum() == 4) {


        bool nonMetalNeighbors = true;
        FOR_NBORS_OF_ATOM(neighbor, &*atom) {
          switch (neighbor->GetAtomicNum()) {
          case 1:
          case 5: case 6: case 7: case 8: case 9:
          case 14: case 15: case 16: case 17:
          case 33: case 34: case 35:
          case 53:
            continue;
          default:
            nonMetalNeighbors = false;
            break;
          }
        }
        if (nonMetalNeighbors)
          atom->SetFormalCharge(+1);
      }


      if (atom->GetFormalCharge() != 0)
        continue;


      if (atom->GetValence() != 0) {
        int nonWaterBonds = 0;
        FOR_NBORS_OF_ATOM(neighbor, &*atom) {
          if (!CIFisWaterOxygen(&*neighbor)) {
            nonWaterBonds = 1;
            break;
          }
        }
        if (nonWaterBonds)
          continue;
      }

      switch(atom->GetAtomicNum()) {
      case 3: case 11: case 19: case 37: case 55: case 87:

        atom->SetFormalCharge(+1);
        break;
      case 4: case 12: case 20: case 38: case 56: case 88:

        atom->SetFormalCharge(+2);
        break;
      case 9: case 17: case 35: case 53: case 85:

        atom->SetFormalCharge(-1);
        break;
      }
    }
  }
