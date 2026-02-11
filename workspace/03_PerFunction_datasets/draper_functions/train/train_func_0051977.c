main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("ERROR: Please provide the command to execute.\n\n");
    print_usage();
    exit(-1);
  }


  if (strcmp(argv[1], "similarity") == 0) {
    return do_similarity(argc, argv);
  }

  else if (strcmp(argv[1], "threshold") == 0) {
    return do_threshold(argc, argv);
  }

  else if (strcmp(argv[1], "extract") == 0) {
    return do_extract(argc, argv);
  }


  else if (strcmp(argv[1], "help") == 0) {
    if (argc == 3) {
      if (strcmp(argv[2], "similarity") == 0) {
        print_similarity_usage();
      }
      if (strcmp(argv[2], "threshold") == 0) {
        print_threshold_usage();
      }
      if (strcmp(argv[2], "extract") == 0) {
        print_extract_usage();
      }
    }
    else {
      print_usage();
    }
  }
  else {
    printf("ERROR: Unknown command.\n\n");
    print_usage();
    exit(-1);
  }
  return 0;
}
