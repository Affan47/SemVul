main(int argc, char *argv[])
{
  if(argc > 1) {
    run_from_file(argv[1]);
  } else {
    fprintf(stderr, "Error: Please specify a .svm compiled bytecode file.\n");
    return -1;
  }


  return 0;
}
