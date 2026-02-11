main(int argc, char** argv)
{
  int i;
  const char* tokens[2];

  if (argc < 3)
    die3(111, "usage: ", program, " cvmodule program [args ...]");

  get_data();
  tokens[0] = pass;
  tokens[1] = 0;
  if ((i = cvm_client_authenticate_password(argv[1], buffer,
					    ucspi_localhost(),
					    pass, 1)) != 0)
    return i;

  if (!cvm_client_setugid()) return 111;
  if (!cvm_client_setenv()) return 111;

  execvp(argv[2], argv+2);
  return 111;
}
