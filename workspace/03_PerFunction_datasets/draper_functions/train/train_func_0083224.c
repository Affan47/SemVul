initName()
{
  if ( name == NULL || name[0] == '\0' ) {
    strstream strm;
    strm << "Layer" << tag << ends;

    update_dyna_string(name, strm.str());
  }
}
