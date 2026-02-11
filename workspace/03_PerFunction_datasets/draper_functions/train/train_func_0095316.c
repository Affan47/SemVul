ReadMolecule(OBBase* pOb, OBConversion* pConv)
{

    OBMol* pmol = pOb->CastAndClear<OBMol>();
    if(pmol==NULL)
        return false;


    istream &ifs = *pConv->GetInStream();
    OBMol &mol = *pmol;
    const char* title = pConv->GetTitle();

    int i;
    int natoms;
    char buffer[BUFF_SIZE];

    ifs.getline(buffer,BUFF_SIZE);
    ifs.getline(buffer,BUFF_SIZE);
    sscanf(buffer,"%d", &natoms);
    if (!natoms)
        return(false);

    mol.ReserveAtoms(natoms);
    mol.BeginModify();

    string str;
    double x,y,z;
    OBAtom *atom;
    vector<string> vs;

    for (i = 1; i <= natoms; i ++)
    {
        if (!ifs.getline(buffer,BUFF_SIZE))
            return(false);
        tokenize(vs,buffer);
        if (vs.size() != 4)
            return(false);
        atom = mol.NewAtom();
        x = atof((char*)vs[1].c_str());
        y = atof((char*)vs[2].c_str());
        z = atof((char*)vs[3].c_str());
        atom->SetVector(x,y,z);


        atom->SetAtomicNum(atoi((char*)vs[0].c_str()));
    }
    if (!pConv->IsOption("b",OBConversion::INOPTIONS))
      mol.ConnectTheDots();
    if (!pConv->IsOption("s",OBConversion::INOPTIONS) && !pConv->IsOption("b",OBConversion::INOPTIONS))
      mol.PerceiveBondOrders();


    while(ifs.peek() != EOF && ifs.good() &&
	  (ifs.peek() == '\n' || ifs.peek() == '\r'))
      ifs.getline(buffer,BUFF_SIZE);

    mol.EndModify();
    mol.SetTitle(title);
    return(true);
}
