fix_case(CasePattern case_pattern,
                          char * res, const char * str) const
  {
    if (!str[0]) return;
    if (case_pattern == AllUpper) {
      to_upper(res,str);
    } if (case_pattern == FirstUpper && is_lower(str[0])) {
      *res = to_title(str[0]);
      if (res == str) return;
      res++;
      str++;
      while (*str) *res++ = *str++;
      *res = '\0';
    } else {
      if (res == str) return;
      while (*str) *res++ = *str++;
      *res = '\0';
    }
  }
