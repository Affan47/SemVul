parse_constraints(struct csa *csa)
{     int i, len, type;
      double s;

      xassert(csa->token == T_SUBJECT_TO);
      scan_token(csa);
loop:
      i = glp_add_rows(csa->P, 1);

      if (csa->token == T_NAME && csa->c == ':')
      {
         if (glp_find_row(csa->P, csa->image) != 0)
            error(csa, "constraint '%s' multiply defined\n",
               csa->image);
         glp_set_row_name(csa->P, i, csa->image);
         scan_token(csa);
         xassert(csa->token == T_COLON);
         scan_token(csa);
      }
      else
      {
         char name[50];
         sprintf(name, "r.%d", csa->count);
         glp_set_row_name(csa->P, i, name);
      }

      len = parse_linear_form(csa);
      glp_set_mat_row(csa->P, i, len, csa->ind, csa->val);

      if (csa->token == T_LE)
         type = GLP_UP, scan_token(csa);
      else if (csa->token == T_GE)
         type = GLP_LO, scan_token(csa);
      else if (csa->token == T_EQ)
         type = GLP_FX, scan_token(csa);
      else
         error(csa, "missing constraint sense\n");

      if (csa->token == T_PLUS)
         s = +1.0, scan_token(csa);
      else if (csa->token == T_MINUS)
         s = -1.0, scan_token(csa);
      else
         s = +1.0;
      if (csa->token != T_NUMBER)
         error(csa, "missing right-hand side\n");
      glp_set_row_bnds(csa->P, i, type, s * csa->value, s * csa->value);

      if (!(csa->c == '\n' || csa->c == XEOF))
         error(csa, "invalid symbol(s) beyond right-hand side\n");
      scan_token(csa);


      if (csa->token == T_PLUS || csa->token == T_MINUS ||
          csa->token == T_NUMBER || csa->token == T_NAME) goto loop;
      return;
}
