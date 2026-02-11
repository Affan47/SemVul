argsfirst(int argc, char **argv)
{

  args_index = 0;
  args_argpos = 0;
  args_value = (char *) (0);


  if ((argv == (char **) (0))
      || (args_index >= argc)) {

    return -1;
  }

  args_value = argv[0];
  argsnext(argc, argv);
  return 0;
}
