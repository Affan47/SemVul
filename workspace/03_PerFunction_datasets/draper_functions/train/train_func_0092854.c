WriteBondStereo(OBBond* pbond, vector<string>& atomIDs)
  {
    static const xmlChar C_ATOMREFS4[]  = "atomRefs4";
    static const xmlChar C_BONDSTEREO[] = "bondStereo";

    char ch=0;
    if(pbond->IsWedge())
      ch='W';
    else if(pbond->IsHash())
      ch='H';

    if(ch)

      xmlTextWriterStartElementNS(writer(), prefix, C_BONDSTEREO, NULL);
    else
    {

      int ud1=0, ud2=0;
      int idx1=0, idx2=0;
      OBAtom* patomA = pbond->GetBeginAtom();
      FOR_BONDS_OF_ATOM(b1,patomA)
        {
          if(b1->IsUp() || b1->IsDown() )
            {
              idx1=(b1->GetNbrAtom(patomA))->GetIdx();
              ud1 = b1->IsDown() ? -1 : 1;


              if((b1->GetNbrAtom(patomA))->HasDoubleBond())
                ud1 = -ud1;
              break;
            }
        }
      OBAtom* patomB = pbond->GetEndAtom();
      FOR_BONDS_OF_ATOM(b2,patomB)
        {
          if(b2->IsUp() || b2->IsDown() )
            {
              idx2=(b2->GetNbrAtom(patomB))->GetIdx();
              ud2 = b2->IsDown() ? -1 : 1;
              break;
            }
        }
      if(!ud1 || !ud2)
        return;

      xmlTextWriterStartElementNS(writer(), prefix, C_BONDSTEREO, NULL);
      xmlTextWriterWriteFormatAttribute(writer(), C_ATOMREFS4, "%s %s %s %s",

            atomIDs[idx1].c_str(), atomIDs[patomA->GetIdx()].c_str(),
            atomIDs[patomB->GetIdx()].c_str(), atomIDs[idx2].c_str());
      ch = (ud1==ud2) ? 'C' : 'T';
    }

    xmlTextWriterWriteFormatString(writer(),"%c", ch);
    xmlTextWriterEndElement(writer());
  }
