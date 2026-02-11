glmReadPPM(char* filename, int* width, int* height)
{
  FILE* fp;
  int i, w, h, d;
  unsigned char* image;
  char head[70];

  fp = fopen(filename, "rb");
  if (!fp) {
    perror(filename);
    return NULL;
  }


  if(NULL==fgets(head, 70, fp)) {
    error("_glmReadPPM() failed reading header"); return NULL;
  }
  if (strncmp(head, "P6", 2)) {
    error("%s: Not a raw PPM file", filename);
    return NULL;
  }


  i = 0;
  while(i < 3) {
    if(NULL==fgets(head, 70, fp)) {
      error("_glmReadPPM() failed header info"); return NULL;
    }
    if (head[0] == '#')
      continue;
    if (i == 0)
      i += sscanf(head, "%d %d %d", &w, &h, &d);
    else if (i == 1)
      i += sscanf(head, "%d %d", &h, &d);
    else if (i == 2)
      i += sscanf(head, "%d", &d);
  }


  image = (unsigned char*)malloc(sizeof(unsigned char)*w*h*3);
  size_t count = fread(image, sizeof(unsigned char), w*h*3, fp);
  fclose(fp);
  if(count!=static_cast<size_t>(w*h*3)) {
    error("_glmReadPPM failed to read all bytes");
    *width=*height=0;
    free(image);
    image=NULL;
    return NULL;
  }

  *width = w;
  *height = h;
  return image;
}
