in_conformity (NODE_T *p)
{
  for (; p != NO_NODE; FORWARD (p))
  {
    if (IS (p, CASE_PART) || IS (p, OUSE_PART)) {
      NODE_T *what = NO_NODE;
      int pop_ind = ind;
      put_sym (SUB (p), KEYWORD);
      BLANK;
      ind = col;
      in_serial (NEXT_SUB (p), !ONE_LINER, &what);
      ind = pop_ind;
      put_nl ();
    } else if (IS (p, CONFORMITY_IN_PART)) {
      NODE_T *what = NO_NODE;
      int pop_ind = ind;
      put_sym (SUB (p), KEYWORD);
      BLANK;
      ind = col;
      in_generic_list (NEXT_SUB (p), &what, ONE_LINER);
      ind = pop_ind;
      put_nl ();
    } else if (IS (p, OUT_PART)) {
      NODE_T *what = NO_NODE;
      int pop_ind = ind;
      put_sym (SUB (p), KEYWORD);
      BLANK;
      ind = col;
      in_serial (NEXT_SUB (p), !ONE_LINER, &what);
      ind = pop_ind;
      put_nl ();
    } else if (IS (p, CONFORMITY_OUSE_PART)) {
      in_conformity (SUB (p));
    } else if (IS (p, ESAC_SYMBOL)) {
      put_sym (p, KEYWORD);
    } else if (IS (p, OPEN_PART)) {
      NODE_T *what = NO_NODE;
      put_sym (SUB (p), KEYWORD);
      in_serial (NEXT_SUB (p), ONE_LINER, &what);
    } else if (IS (p, ELSE_OPEN_PART)) {
      NODE_T *what = NO_NODE;
      BLANK;
      put_sym (SUB (p), KEYWORD);
      BLANK;
      in_serial (NEXT_SUB (p), ONE_LINER, &what);
    } else if (IS (p, CONFORMITY_CHOICE)) {
      NODE_T *what = NO_NODE;
      BLANK;
      put_sym (SUB (p), KEYWORD);
      BLANK;
      in_generic_list (NEXT_SUB (p), &what, ONE_LINER);
    } else if (IS (p, CHOICE)) {
      NODE_T *what = NO_NODE;
      BLANK;
      put_sym (SUB (p), KEYWORD);
      BLANK;
      in_serial (NEXT_SUB (p), ONE_LINER, &what);
    } else if (IS (p, BRIEF_CONFORMITY_OUSE_PART)) {
      in_conformity (SUB (p));
    } else if (IS_CLOSE_SYMBOL (p)) {
      put_sym (p, KEYWORD);
    }
  }
}
