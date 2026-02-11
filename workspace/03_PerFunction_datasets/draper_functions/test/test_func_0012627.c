optimize ()
{

  prepare ();


  find_positions ();


  find_alpha_inc ();


  find_good_asso_values ();


  _collision_detector->clear ();
  for (KeywordExt_List *curr_ptr = _head; curr_ptr; curr_ptr = curr_ptr->rest())
    {
      KeywordExt *curr = curr_ptr->first();
      unsigned int hashcode = compute_hash (curr);
      if (_collision_detector->set_bit (hashcode))
        {


          fprintf (stderr,
                   "\nInternal error, unexpected duplicate hash code\n");
          if (option[POSITIONS])
            fprintf (stderr, "try options -m or -r, or use new key positions.\n\n");
          else
            fprintf (stderr, "try options -m or -r.\n\n");
          exit (1);
        }
    }


  sort ();


  int max_hash_value;
  {
    KeywordExt_List *temp;
    for (temp = _head; temp->rest(); temp = temp->rest())
      ;
    max_hash_value = temp->first()->_hash_value;
  }
  for (unsigned int c = 0; c < _alpha_size; c++)
    if (_occurrences[c] == 0)
      _asso_values[c] = max_hash_value + 1;


  if (_alpha_unify)
    for (unsigned int c = 0; c < _alpha_size; c++)
      if (_alpha_unify[c] != c)
        _asso_values[c] = _asso_values[_alpha_unify[c]];
}
