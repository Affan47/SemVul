new_array(uint8_t type)
{
  if (!temp_var)
  {
    fprintf(out, "  int32_t temp;\n");
    temp_var = true;
  }

  fprintf(out, "  temp = stack_%d;\n", stack - 1);

  if (type == TYPE_SHORT || type == TYPE_CHAR)
  {
    fprintf(out, "  stack_%d = (int32_t)malloc(temp * 2 + 4);\n", stack - 1);
  }
    else
  if (type == TYPE_INT)
  {
    fprintf(out, "  stack_%d = (int32_t)malloc(temp * 4 + 4);\n", stack - 1);
  }
    else
  {
    fprintf(out, "  stack_%d = (int32_t)malloc(temp + 4);\n", stack - 1);
  }

  fprintf(out, "  *((int32_t *)stack_%d) = temp;\n", stack - 1);
  fprintf(out, "  stack_%d += 4;\n", stack - 1);

  return 0;
}
