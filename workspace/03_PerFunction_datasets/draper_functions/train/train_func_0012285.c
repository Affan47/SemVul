generate_exhaustive_fast_canonicalization()
{
  fprintf(codefile,
          "\n/********************\n"
          " Canonicalization by fast exhaustive generation of\n"
          " all permutations\n"
          " ********************/\n");

  fprintf(codefile,
	  "void SymmetryClass::Exhaustive_Fast_Canonicalize(state* s)\n"
	  "{\n"
	  "  int i;\n"
	  "  static state temp;\n"
	  "  Perm.ResetToExplicit();\n"
          "\n"
	  );

  for ( stelist * var = varlist; var != NULL; var = var->next )
    fprintf(codefile,
	    "  StateCopy(&temp, workingstate);\n"
            "  ResetBestResult();\n"
            "  for (i=0; i<Perm.count; i++)\n"
            "    if (Perm.In(i))\n"
            "      {\n"
            "        StateCopy(workingstate, &temp);\n"
            "        %s.Permute(Perm,i);\n"
	    "        if (args->multiset_reduction.value)\n"
	    "          %s.MultisetSort();\n"
            "        SetBestResult(i, workingstate);\n"
            "      }\n"
            "  StateCopy(workingstate, &BestPermutedState);\n"
            "\n",
            var->s->getvalue()->mu_name,
            var->s->getvalue()->mu_name
            );
  fprintf(codefile,
	  "};\n");
}
