main(int argc, char **argv) {

  int ret, zoom, tmp;
  img_t img;
  char *output_dir;
  int output_format = PNG;

  if (argc < 6) {
    printf("Usage:\ntilegen <input.png> <output_dir> <tileX> <tileY> <max_zoom> [cardinal_direction N|E|S|W]\n");
    exit(1);
  }

  if (strstr(argv[0], "jpg"))
    output_format = JPG;

  printf("Read file \"%s\"\n", argv[1]);
  if (strstr(argv[1], ".png"))
    ret = read_png(argv[1], &img);
  else if (strstr(argv[1], ".ppm"))
    ret = read_ppm(argv[1], &img);
  else {
    printf("Unknown format!\n");
    exit(2);
  }

  output_dir = argv[2];

  if (ret) {
    printf("Could not read png input file! %d\n", ret);
    exit(ret);
  }

  img.tileX = atoi(argv[3]);
  img.tileY = atoi(argv[4]);
  zoom = atoi(argv[5]);

  if (argc > 6) {
    switch(argv[6][0]) {
    case 'n':
    case 'N':

      break;
    case 'e':
    case 'E':
      tmp = img.tileX;
      img.tileX = img.tileY;
      img.tileY = (2<<12) - 1 - tmp;
      break;
    case 's':
    case 'S':
      img.tileX = (2<<12) - 1 - img.tileX;
      img.tileY = (2<<12) - 1 - img.tileY;
      break;
    case 'w':
    case 'W':
      tmp = img.tileX;
      img.tileX = (2<<12) - 1 - img.tileY;
      img.tileY = tmp;
      break;
    default:
      fprintf(stderr, "Unknown cardinal direction \"%s\". Default to north\n", argv[6]);
    }
  }

  while (1) {

    printf("Processing zoom %d\n", zoom);


    crop_image(&img, zoom, output_dir, output_format);


    if (img.sizeX == TILE_SIZE)
      break;

    scale_image(&img);
    zoom--;
  }

  return 0;
}
