affects_prev (char c, List_Node *curr)
{
  int const original_char = Vectors::asso_values[(int) c];
  int total_iterations = 0;

  if (!option[FAST])
    {
      total_iterations = option.asso_max ();
    }
  else
    {
      total_iterations = option.iterations ();

      if (total_iterations == 0)
        total_iterations = this->key_list.keyword_list_length ();
    }


  for (int i = total_iterations - 1; i >= 0; --i)
    {
      Vectors::asso_values[(int) c] =
        (Vectors::asso_values[(int) c]
         + (option.jump () ? option.jump () : ACE_OS::rand ()))
        & (option.asso_max () - 1);


      this->char_search.reset ();

      int collisions = 0;


      for (List_Node *ptr = this->key_list.head;
           this->char_search.find (this->hash (ptr)) == 0
           || ++collisions < fewest_collisions;
           ptr = ptr->next)
        {
          if (ptr == curr)
            {
              fewest_collisions = collisions;

              if (option[DEBUGGING])
                {
                  ACE_DEBUG ((LM_DEBUG,
                              "- resolved after %d iterations",
                              total_iterations - i));
                }

              return 0;
            }
        }
    }


  Vectors::asso_values[(int) c] = original_char;


  return 1;
}
