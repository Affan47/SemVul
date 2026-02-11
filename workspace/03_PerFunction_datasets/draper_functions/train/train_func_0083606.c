RevertToAliasForm(OBMol& mol)
{


  bool acted;
  do
  {
    FOR_ATOMS_OF_MOL(a, mol)
    {
      acted=false;
      AliasData* ad = NULL;
      if((ad = (static_cast<AliasData*>(a->GetData(AliasDataType)))) && ad->IsExpanded())
      {
        ad->DeleteExpandedAtoms(mol);
        acted = true;
        break;
      }
    }
  }while(acted);
}
