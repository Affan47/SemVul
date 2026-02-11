get_size_ppm(const char *name, int &height, int &width)
   {
      char buf[PNM_BUFFER_SIZE];


      std::ifstream file(name, std::ios::in | std::ios::binary);
      pnm_read(file, buf);
      if (strncmp(buf, "P6", 2))
      {
         printf("type mismatch\n");
         exit(1);
      }

      pnm_read(file, buf);
      width = atoi(buf);

      pnm_read(file, buf);
      height = atoi(buf);

      file.close();
      return;
   }
