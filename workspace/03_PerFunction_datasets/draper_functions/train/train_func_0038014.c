dumpVPSCException(char const *str, IncSolver* solver) {
    cerr<<str<<endl;
    unsigned m;
    Constraint** cs = solver->getConstraints(m);
    for(unsigned i=0;i<m;i++) {
        cerr << *cs[i] << endl;
    }
}
