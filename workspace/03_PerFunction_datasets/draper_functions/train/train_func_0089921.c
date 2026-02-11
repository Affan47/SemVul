checkLastTag(bool being_deleted)
{
  int last_tag = getLastTag();


  if ( last_tag == NO_INDEX )
    return;


  if (being_deleted) {
    if (last_tag == tag) {
      last_tag--;
    }
  }


  else {
    if (last_tag < tag) {
      last_tag = tag;
    }
  }

  setLastTag(last_tag);
}
