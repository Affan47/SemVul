read_hierarchy( CMtz::MTZ* mtzin, std::vector<CCP4MTZfile::crystalinf>& crystals )
{
  crystals.clear();
  CCP4MTZfile::crystalinf newxtl;
  CCP4MTZfile::datasetinf newset;
  CCP4MTZfile::datacolinf newcol;
  for (int x=0; x < CMtz::MtzNxtal(mtzin); x++) {
    CMtz::MTZXTAL* xtl = CMtz::MtzIxtal(mtzin,x);
    newxtl.crystal = MTZcrystal( xtl->xname, xtl->pname, Cell( Cell_descr( xtl->cell[0], xtl->cell[1], xtl->cell[2], xtl->cell[3], xtl->cell[4], xtl->cell[5] ) ) );
    crystals.push_back( newxtl );
    for (int s=0; s < CMtz::MtzNsetsInXtal(xtl); s++) {
      CMtz::MTZSET* set = CMtz::MtzIsetInXtal(xtl,s);
      newset.dataset = MTZdataset( set->dname, set->wavelength );
      crystals.back().datasets.push_back( newset );
      for (int c=0; c < CMtz::MtzNcolsInSet(set); c++) {
        const CMtz::MTZCOL* col = CMtz::MtzIcolInSet(set,c);
	newcol.label = col->label;
	newcol.type  = col->type;
	crystals.back().datasets.back().columns.push_back( newcol );
      }
    }
  }
}
