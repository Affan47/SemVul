main(int argc, char **argv)
{
   char *file;
   int w, h, i;
   int head_only = 0;

   if (argc < 2) return -1;

   file = argv[1];
   for (i = 2; i < argc; i++)
     {
        if      (!strcmp(argv[i], "-head"))

           head_only = 1;
        else if (!strcmp(argv[i], "-key"))
          {
             i++;

          }
        else if (!strcmp(argv[i], "-opt-scale-down-by"))
          {
             i++;

          }
        else if (!strcmp(argv[i], "-opt-dpi"))
          {
             i++;

          }
        else if (!strcmp(argv[i], "-opt-size"))
          {
             i++;

             i++;

          }
     }

   timeout_init(8);

   D("xcf_file_init\n");
   if (!xcf_file_init(file)) return -1;

   D("size %i %i\n", image->width, image->height);
   if (!head_only)
     {
        xcf_load_image();
        premul_image();
     }
   w = image->width;
   h = image->height;
   printf("size %i %i\n", w, h);
   printf("alpha 1\n");
   if (!head_only)
     {
        if (shm_fd >= 0) printf("shmfile %s\n", shmfile);
        else
          {


             printf("data\n");
             fwrite(image->data, w * h * sizeof(DATA32), 1, stdout);
          }
        shm_free();
     }
   else
      printf("done\n");
   xcf_cleanup();
   return 0;
}
