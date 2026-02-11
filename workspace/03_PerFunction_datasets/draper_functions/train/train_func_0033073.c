fileset(FILE * fp, int c, size_t n)
{
#define BLOCK_SIZE (1024)
 int block[BLOCK_SIZE];
 size_t left_to_write = n;

 memset(block, c, sizeof(block));

 while(left_to_write > 0)
 {
   size_t write = sizeof(block);
   if (write > left_to_write) write = left_to_write;

   if (1 != fwrite(block, write, 1, fp))
   {
     fclose(fp);
     fatal("ERROR: The disk image is not complete - could not write data block!");
   }

   left_to_write -= write;
 }
}
