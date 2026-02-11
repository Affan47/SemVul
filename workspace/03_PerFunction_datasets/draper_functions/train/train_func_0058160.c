findHash ( const char *name , int section ) const
{
  COINColumnIndex found = -1;

  char ** names = names_[section];
  CoinHashLink * hashThis = hash_[section];
  COINColumnIndex maxhash = 4 * numberHash_[section];
  COINColumnIndex ipos;


  if ( !maxhash )
    return -1;
  int length = static_cast<int>(strlen(name));

  ipos = hash ( name, maxhash, length );
  while ( 1 ) {
    COINColumnIndex j1 = hashThis[ipos].index;

    if ( j1 >= 0 ) {
      char *thisName2 = names[j1];

      if ( strcmp ( name, thisName2 ) != 0 ) {
	COINColumnIndex k = hashThis[ipos].next;

	if ( k != -1 )
	  ipos = k;
	else
	  break;
      } else {
	found = j1;
	break;
      }
    } else {
      found = -1;
      break;
    }
  }
  return found;
}
