output_types (void)
{
  if (option[TYPE])
    {
      delete [] array_type_;
      array_type_ = array_type ();
      if (array_type_ == 0)

        return -1;
      else
        {

          size_t struct_tag_length = ACE_OS::strcspn (array_type_,
                                                      "{\n\0");
          if (option[POINTER])
            {
              delete [] return_type;
              ACE_NEW_RETURN (return_type,
                              char[struct_tag_length + 2],
                              -1);
              ACE_OS::strncpy (return_type,
                               array_type_,
                               struct_tag_length);
              return_type[struct_tag_length] = '*';
              return_type[struct_tag_length + 1] = '\0';
            }

          delete [] struct_tag;
          ACE_NEW_RETURN (struct_tag,
                          char[struct_tag_length + 2],
                          -1);
          ACE_OS::strncpy (struct_tag,
                           array_type_,
                           struct_tag_length);
          if (struct_tag[struct_tag_length - 1] != ' ')
            {
              struct_tag[struct_tag_length] = ' ';
              ++struct_tag_length;
            }
          struct_tag[struct_tag_length] = '\0';
        }
    }
  else if (option[POINTER])
    {
      delete [] return_type;
      return_type = dup_string (Key_List::default_array_type);
    }
  return 0;
}
