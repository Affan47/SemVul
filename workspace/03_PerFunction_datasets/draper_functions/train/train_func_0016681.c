copyMatcValueTable(MatcValueTable& source, MatcValueTable& target)
{
  MatcValueTable::iterator pos = source.begin();
  MatcValueTable::iterator end_pos = source.end();

  while ( pos != end_pos ) {


    const char* key = (*pos).first.c_str();
    char* val = (*pos).second;


    char* old_val = target[key];
    if ( old_val != NULL ) {
      delete[] old_val;
      target.erase(key);
    }


    char* new_val;
    create_dyna_string(new_val, val);


    target[key] = new_val;

    pos++;
  }
}
