getpicsize( void* hd2, int &width, int &height)
{
   trleheader* hd = (trleheader*) hd2;
   if (hd->id == 16973) {
      width = hd->x;
      height = hd->y;
   } else {
     width = hd->id + 1;
     height = hd->size + 1;
   }
}
