create_reaction_texture (void)
{
   int i,j;
   Texture * tex;
   unsigned char * pixmap;

   pixmap = (unsigned char *)
              malloc (TEXTURE_SIZE*TEXTURE_SIZE*3* sizeof (unsigned char));

   for (i=0; i< TEXTURE_SIZE; i++) {
      for (j=0; j<TEXTURE_SIZE; j++) {
         CPfield[i][j] = ((float) ((i*j)%4096)) / 4096.0;
         CMfield[i][j] = ((float) ((i*i+j*j)%8192)) / 8192.0;
         RPfield[i][j] = 0.0;
         RMfield[i][j] = 0.0;
      }
   }

   for (i=0; i< TEXTURE_SIZE; i++) {
      for (j=0; j<TEXTURE_SIZE; j++) {
         pixmap [3*TEXTURE_SIZE*i+3*j] =  255.0 * CPfield[i][j];
         pixmap [3*TEXTURE_SIZE*i+3*j+1] = 127.0 * (CPfield[i][j]+CMfield[i][j]);
         pixmap [3*TEXTURE_SIZE*i+3*j+2] = 255.0 * CMfield[i][j];
      }
   }

   tex = (Texture *) malloc (sizeof (Texture));
   tex -> size = TEXTURE_SIZE;
   tex -> pixmap = pixmap;

   reaction_texture = tex;
   return tex;
}
