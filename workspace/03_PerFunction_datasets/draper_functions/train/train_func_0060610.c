read(bool readProperties, Properties::ReadStyle audioPropertiesStyle)
{
  if(!isValid())
    return;

  d->atoms = new Atoms(this);
  if (!checkValid(d->atoms->atoms)) {
    setValid(false);
    return;
  }


  MP4::Atom *moov = d->atoms->find("moov");
  if(!moov) {
    setValid(false);
    return;
  }

  d->tag = new Tag(this, d->atoms);
  if(readProperties) {
    d->properties = new Properties(this, d->atoms, audioPropertiesStyle);
  }
}
