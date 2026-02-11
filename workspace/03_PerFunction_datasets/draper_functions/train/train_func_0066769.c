cbf_copy_strings (cbf_context *context,
                                  const char *string1,
                                  const char *string2,
                                  char type)
    {
        char *new_string;

        void *memblock;

        if (!string1) return cbf_copy_string(context,string2,type);

        if (!string2) return cbf_copy_string(context,string2,type);

        if (type)
        {
            if (cbf_alloc (&memblock, NULL,
                           sizeof (char),
                           strlen (string1) + strlen(string2) + 2) == 0)
            {
                new_string = (char *)memblock;

                *new_string = type;

                strcpy (new_string + 1, string1);

                strcpy (new_string + 1 + strlen(string1),string2);

                return new_string;
            }
        }

        if (cbf_alloc (&memblock, NULL,
                       sizeof (char),
                       strlen (string1) + strlen(string2) + 1) == 0)
        {

            new_string = (char *)memblock;

            strcpy (new_string, string1);

            strcpy (new_string + strlen(string1), string2);

            return new_string;
        }

        return NULL;

    }
