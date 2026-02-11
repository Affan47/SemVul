Translate(const vector3 &v,int nconf)
  {
    obErrorLog.ThrowError(__FUNCTION__,
                          "Ran OpenBabel::Translate", obAuditMsg);

    int i,size;
    double x,y,z;
    double *c = (nconf == OB_CURRENT_CONFORMER)? _c : GetConformer(nconf);

    x = v.x();
    y = v.y();
    z = v.z();
    size = NumAtoms();
    for (i = 0;i < size;++i)
      {
        c[i*3  ] += x;
        c[i*3+1] += y;
        c[i*3+2] += z;
      }
  }
