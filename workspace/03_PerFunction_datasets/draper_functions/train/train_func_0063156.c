read_rows(struct csa *csa)
{
      int i, type;
loop: if (indicator(csa, 0)) goto done;

      read_field(csa), strspx(csa->field);
      if (strcmp(csa->field, "N") == 0)
         type = GLP_FR;
      else if (strcmp(csa->field, "G") == 0)
         type = GLP_LO;
      else if (strcmp(csa->field, "L") == 0)
         type = GLP_UP;
      else if (strcmp(csa->field, "E") == 0)
         type = GLP_FX;
      else if (csa->field[0] == '\0')
         error(csa, "missing row type in field 1\n");
      else
         error(csa, "invalid row type in field 1\n");

      read_field(csa), patch_name(csa, csa->field);
      if (csa->field[0] == '\0')
         error(csa, "missing row name in field 2\n");
      if (glp_find_row(csa->P, csa->field) != 0)
         error(csa, "row `%s' multiply specified\n", csa->field);
      i = glp_add_rows(csa->P, 1);
      glp_set_row_name(csa->P, i, csa->field);
      glp_set_row_bnds(csa->P, i, type, 0.0, 0.0);

      skip_field(csa);
      skip_field(csa);
      skip_field(csa);
      skip_field(csa);
      goto loop;
done: return;
}
