operator<<(ostream &out, const OpenBabel::OBSquarePlanarStereo &ct)
  {
    OpenBabel::OBSquarePlanarStereo::Config cfg = ct.GetConfig();
    out << "OBSquarePlanarStereo(center = " << cfg.center;

    out << ", refs = ";
    for (OpenBabel::OBStereo::Refs::iterator i = cfg.refs.begin(); i != cfg.refs.end(); ++i)
      if (*i != OpenBabel::OBStereo::ImplicitRef)
        out << *i << " ";
      else
        out << "H ";

    switch (cfg.shape) {
      case OpenBabel::OBStereo::ShapeU:
        out << ", shape = U)";
        break;
      case OpenBabel::OBStereo::ShapeZ:
        out << ", shape = Z)";
        break;
      case OpenBabel::OBStereo::Shape4:
        out << ", shape = 4)";
        break;
    }

    return out;
  }
