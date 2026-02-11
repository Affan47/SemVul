main(int argc,char **argv)
{
  char *program_name= argv[0];
  char *FileIn = NULL;

  if (argc != 2)
    {
      cout << "Usage: " << program_name << " <filename>" << endl;
      exit(-1);
    }
  else
    {
      FileIn  = argv[1];

    }


  OBConversion conv;
  OBFormat *format = conv.FormatFromExt(FileIn);

  if (!format || !conv.SetInAndOutFormats(format, format))
    {
      cerr << program_name << ": cannot read input format!" << endl;
      exit (-1);
    }

  ifstream ifs;


  ifs.open(FileIn);
  if (!ifs)
    {
      cerr << program_name << ": cannot read input file!" << endl;
      exit (-1);
    }

  OBMol mol;
  OBAtom *atom;

  for (int c=1;;++c)
    {
      mol.Clear();
      conv.Read(&mol, &ifs);
      if (mol.Empty())
        break;
      cout << "Molecule "<< c << ": " << mol.GetTitle() << endl;

      vector<OBAtom*>::iterator i;
      for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
        {
          if(!atom->IsChiral())continue;
          cout << "Atom " << atom->GetIdx() << " Is Chiral ";
          cout << atom->GetType()<<endl;

          OBChiralData* cd = (OBChiralData*)atom->GetData(OBGenericDataType::ChiralData);

          if (cd){
            vector<unsigned int> x=cd->GetAtom4Refs(input);
            size_t n=0;
            cout <<"Atom4refs:";
            for (n=0;n<x.size();++n)
              cout <<" "<<x[n];
            cout <<endl;
          }
          else{cd=new OBChiralData;atom->SetData(cd);}
          vector<unsigned int> _output;
          unsigned int n;
          for(n=1;n<5;++n) _output.push_back(n);
          cd->SetAtom4Refs(_output,output);


        }

    }

  return(0);
}
