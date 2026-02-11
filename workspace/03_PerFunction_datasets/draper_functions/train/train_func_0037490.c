main(int argc, char *argv[])
{
  GtArray *features;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s style_file output_file\n", argv[0]);
    return EXIT_FAILURE;
  }

  gt_lib_init();

  features = create_example_features();

  draw_example_features(features, argv[1], argv[2]);

  delete_example_features(features);

  gt_lib_clean();
  return EXIT_SUCCESS;
}
