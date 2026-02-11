get_comp_type(const char **str, enum comparison_type *comp_type)
{
  switch (**str)
    {
    case '+':
      *comp_type = COMP_GT;
      (*str)++;
      break;
    case '-':
      *comp_type = COMP_LT;
      (*str)++;
      break;
    default:
      *comp_type = COMP_EQ;
      break;
    }
  return true;
}
