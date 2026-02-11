list(ostream& os) const {


  os << "\n --------  PYTHIA Partons resolved in beam  -----------------"
     << "-------------------------------------------------------------\n"
     << "\n    i  iPos      id       x    comp   xqcomp    pTfact      "
     << "colours      p_x        p_y        p_z         e          m \n";


  double xSum  = 0.;
  Vec4   pSum;
  for (int i = 0; i < size(); ++i) {
    ResolvedParton res = resolved[i];
    os << fixed << setprecision(6) << setw(5) << i << setw(6) << res.iPos()
       << setw(8) << res.id() << setw(10) << res.x() << setw(6)
       << res.companion() << setw(10) << res.xqCompanion() << setw(10)
       << res.pTfactor() << setprecision(3) << setw(6) << res.col()
       << setw(6) << res.acol() << setw(11) << res.px() << setw(11)
       << res.py() << setw(11) << res.pz() << setw(11) << res.e()
       << setw(11) << res.m() << "\n";


    if (res.companion() != -10) {
      xSum  += res.x();
      pSum  += res.p();
    }
  }


  os << setprecision(6) << "             x sum:" << setw(10) << xSum
     << setprecision(3) << "                                p sum:"
     << setw(11) << pSum.px() << setw(11) << pSum.py() << setw(11)
     << pSum.pz() << setw(11) << pSum.e()
     << "\n\n --------  End PYTHIA Partons resolved in beam  -----------"
     << "---------------------------------------------------------------"
     << endl;
}
