accept(tcPDPtr parent, const tPDVector & children) const {
  if(abs(parent->id()) != ParticleID::t) return false;
  int id0(0),id1(0),id2(0);
  for(tPDVector::const_iterator it = children.begin();
      it != children.end();++it) {
    int id=(**it).id(),absid(abs(id));
    if(absid==ParticleID::b&&double(id)/double(parent->id())>0) {
      id0=id;
    }
    else {
      switch (absid) {
      case ParticleID::nu_e:
      case ParticleID::nu_mu:
      case ParticleID::nu_tau:
	id1 = id;
	break;
      case ParticleID::eminus:
      case ParticleID::muminus:
      case ParticleID::tauminus:
	id2 = id;
	break;
      case ParticleID::b:
      case ParticleID::d:
      case ParticleID::s:
	id1 = id;
	break;
      case ParticleID::u:
      case ParticleID::c:
	id2=id;
	break;
      default :
	break;
      }
    }
  }
  if(id0==0||id1==0||id2==0) return false;
  if(double(id1)/double(id2)>0) return false;
  return true;
}
