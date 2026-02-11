run(void)
{
   do {
      tdialogbox::run();
      if (taste == ct_f1) help(1010);
   }  while (!((taste == ct_esc) || (action >= 2)));
   if (action == 2) setmap();
   for (int i=0;i<layercount ;i++ ) {
      if (initialized[i]) {
         free(mblocks[i]->mempointer);
         free(mblocks[i]);
      }
   }
}
