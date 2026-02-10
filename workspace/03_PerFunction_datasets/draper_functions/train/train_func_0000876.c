output_state_ainsn_table (state_ainsn_table_t tab, char *table_name,
			  void (*output_full_vect_name_func) (FILE *, automaton_t),
			  void (*output_comb_vect_name_func) (FILE *, automaton_t),
			  void (*output_check_vect_name_func) (FILE *, automaton_t),
			  void (*output_base_vect_name_func) (FILE *, automaton_t))
{
  if (!comb_vect_p (tab))
    {
      fprintf (output_file, "/* Vector for %s.  */\n", table_name);
      fprintf (output_file, "static const ");
      output_range_type (output_file, tab->min_comb_vect_el_value,
                         tab->max_comb_vect_el_value);
      fprintf (output_file, " ");
      (*output_full_vect_name_func) (output_file, tab->automaton);
      fprintf (output_file, "[] ATTRIBUTE_UNUSED = {\n");
      output_vect (VLA_HWINT_BEGIN (tab->full_vect),
                   VLA_HWINT_LENGTH (tab->full_vect));
      fprintf (output_file, "};\n\n");
    }
  else
    {
      fprintf (output_file, "/* Comb vector for %s.  */\n", table_name);
      fprintf (output_file, "static const ");
      output_range_type (output_file, tab->min_comb_vect_el_value,
                         tab->max_comb_vect_el_value);
      fprintf (output_file, " ");
      (*output_comb_vect_name_func) (output_file, tab->automaton);
      fprintf (output_file, "[] ATTRIBUTE_UNUSED = {\n");
      output_vect (VLA_HWINT_BEGIN (tab->comb_vect),
                   VLA_HWINT_LENGTH (tab->comb_vect));
      fprintf (output_file, "};\n\n");
      fprintf (output_file, "/* Check vector for %s.  */\n", table_name);
      fprintf (output_file, "static const ");
      output_range_type (output_file, 0, tab->automaton->achieved_states_num);
      fprintf (output_file, " ");
      (*output_check_vect_name_func) (output_file, tab->automaton);
      fprintf (output_file, "[] = {\n");
      output_vect (VLA_HWINT_BEGIN (tab->check_vect),
                   VLA_HWINT_LENGTH (tab->check_vect));
      fprintf (output_file, "};\n\n");
      fprintf (output_file, "/* Base vector for %s.  */\n", table_name);
      fprintf (output_file, "static const ");
      output_range_type (output_file, tab->min_base_vect_el_value,
                         tab->max_base_vect_el_value);
      fprintf (output_file, " ");
      (*output_base_vect_name_func) (output_file, tab->automaton);
      fprintf (output_file, "[] = {\n");
      output_vect (VLA_HWINT_BEGIN (tab->base_vect),
                   VLA_HWINT_LENGTH (tab->base_vect));
      fprintf (output_file, "};\n\n");
    }
}
