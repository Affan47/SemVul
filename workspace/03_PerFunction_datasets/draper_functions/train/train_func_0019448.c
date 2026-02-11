generate_decl()
{
  if (!declared) {
    fprintf(codefile, "const int %s = %d;\n", mu_name, value);
    declared = TRUE;
  }
  return "ERROR!";
}
