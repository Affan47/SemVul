apply_n_classes_fn ( char *n_classes_fn_type, int n_tries, search_try_DS *tries,
                         int  max_j, int explain_p, char *n_classes_explain)
{
  int return_value;

  if (eqstring(n_classes_fn_type, "random_ln_normal"))
    return_value = random_j_from_ln_normal( n_tries, tries, max_j, explain_p,
                                    n_classes_explain);
  else {
    fprintf(stderr, "\nERROR: number of classes function type \"%s\" not handled!\n",
            n_classes_fn_type);
    exit(1);
  }
  return return_value;
}
