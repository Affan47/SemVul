EnumerateProducts(OBMol *scaffold, std::map<std::string, OBAtom*> &scaffoldRMap,
    std::map<std::string, std::vector<RGroup> > &rGroupMap,
    std::map<std::string, std::vector<RGroup> >::iterator iter, OBConversion &conv)
{
  std::string rrr = iter->first;
  std::vector<RGroup> &rGroups = iter->second;
  iter++;
  for (std::size_t i = 0; i < rGroups.size(); ++i) {
    OBMol scaffoldCopy(*scaffold);
    if (scaffoldRMap.find(rrr) == scaffoldRMap.end()) {
      std::cout << "Warning: Could not find substituent R# in scaffold. Ignoring substituent." << std::endl;
      break;
    }
    OBAtom *scaffoldAtom = scaffoldCopy.GetAtom(scaffoldRMap[rrr]->GetIdx());

    scaffoldCopy += *rGroups[i].mol;
    OBAtom *rGroupAtom = scaffoldCopy.GetAtom(scaffold->NumAtoms() + rGroups[i].atom->GetIdx());

    scaffoldCopy.AddBond(scaffoldAtom->GetIdx(), rGroupAtom->GetIdx(), 1);

    if (iter != rGroupMap.end())
      EnumerateProducts(&scaffoldCopy, scaffoldRMap, rGroupMap, iter, conv);
    else {
      generateDiagram(&scaffoldCopy);
      conv.Write(&scaffoldCopy);
      std::cout << "product..." << std::endl;
    }
  }
}
