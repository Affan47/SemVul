set_and_realloc_gde_array(uchar **&the_names, uchar **&the_sequences, long &allocated, long &numberspecies, long &maxalign,
                                      const char *name, int name_len, const char *seq, int seq_len)
{
    if (allocated==numberspecies)
    {
        long new_allocated = (allocated*3)/2;

        the_names = (uchar**)GB_recalloc(the_names, allocated, new_allocated, sizeof(*the_names));
        the_sequences = (uchar**)GB_recalloc(the_sequences, allocated, new_allocated, sizeof(*the_sequences));
        allocated = new_allocated;
    }

    the_names[numberspecies] = (uchar*)GB_calloc(name_len+1, sizeof(char));
    memcpy(the_names[numberspecies], name, name_len);
    the_names[numberspecies][name_len] = 0;
    replaceChars((char*)the_names[numberspecies], ' ', '_');

    the_sequences[numberspecies] = (uchar*)GB_calloc(seq_len+1, sizeof(char));
    memcpy(the_sequences[numberspecies], seq, seq_len);
    the_sequences[numberspecies][seq_len] = 0;

    if (seq_len>maxalign) {
        maxalign = seq_len;
    }

    numberspecies++;
}
