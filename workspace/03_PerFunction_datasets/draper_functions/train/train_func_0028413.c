permutationInvertsCisTransBeginOrEndAtom(const Automorphism &p, OBBond *bond, OBAtom *beginOrEnd,
        const std::vector<unsigned int> &canon_labels)
    {
      OBAtom *otherAtom = bond->GetNbrAtom(beginOrEnd);

      std::vector< std::pair<unsigned int, unsigned int> > tlist1;

      FOR_NBORS_OF_ATOM (nbr, beginOrEnd) {

        if (nbr->GetId() == otherAtom->GetId())
          continue;
        tlist1.push_back(std::make_pair(nbr->GetIndex(), canon_labels[nbr->GetIndex()]));
      }

      std::sort(tlist1.begin(), tlist1.end(), ComparePairSecond);


      std::vector<unsigned long> tlist2;
      for (std::size_t j = 0; j < tlist1.size(); ++j) {
        unsigned int t;
        if (MapsTo(p, tlist1[j].first, t))
          tlist2.push_back(canon_labels[t]);
      }

      return (OBStereo::NumInversions(tlist2) % 2);
    }
