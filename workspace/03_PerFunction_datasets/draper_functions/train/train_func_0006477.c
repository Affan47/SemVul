main(int argc,char *argv[])
{
  if (argc != 2)
    {
      cout << "Usage: obrotamer <file>" << endl;
      cout << "  Outputs the number of rotable bonds and generate a random"
           << " rotamer" << endl;
      return(-1);
    }

  ifstream ifs(argv[1]);
  if (!ifs)
    {
      cerr << "Error! Cannot read input file!" << endl;
      return(-1);
    }

  OBConversion conv(&ifs, &cout);
  OBFormat* pFormat;

  pFormat = conv.FormatFromExt(argv[1]);
  if ( pFormat == NULL )
    {
      cerr << "Error! Cannot read file format!" << endl;
      return(-1);
    }


  OBMol mol;
  if (! conv.SetInAndOutFormats(pFormat, pFormat))
    {
      cerr << "Error! File format isn't loaded" << endl;
      return (-1);
    }

  OBRotorList rl;
  OBRotamerList rotamers;
  int *rotorKey = NULL;
  OBRandom rand;
  rand.TimeSeed();

  while(ifs.peek() != EOF && ifs.good())
    {
      mol.Clear();
      conv.Read(&mol);

      rl.Setup(mol);

      cerr << " Number of rotatable bonds: " << rl.Size() << endl;


      std::vector<int> rotorKey(rl.Size() + 1, 0);


      OBRotorIterator ri;
      OBRotor *rotor = rl.BeginRotor(ri);
      for (int i = 1; i < rl.Size() + 1; ++i, rotor = rl.NextRotor(ri))
        rotorKey[i] = rand.NextInt() % rotor->GetResolution().size();

      rotamers.SetBaseCoordinateSets(mol);
      rotamers.Setup(mol, rl);
      rotamers.AddRotamer(rotorKey);


      rotamers.ExpandConformerList(mol, mol.GetConformers());


      mol.SetConformer(0);
      conv.Write(&mol);
    }

  return(0);
}
