getpicsize2( void* hd2 )
{
   trleheader* hd = (trleheader*) hd2;
   int width;
   int height;
   if (hd->id == 16973)
      return hd->size + sizeof(*hd);
   else {
     width = hd->id + 1;
     height = hd->size + 1;
     return height*width+4;
   }
}
