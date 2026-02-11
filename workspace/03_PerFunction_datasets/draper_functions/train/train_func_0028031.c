getid( const char*  title, int lval,int min,int max)

{ tgetid     gi;
   gi.onCancel = tgetid::ReturnOriginal;

   strcpy( gi.nt, title );
   gi.max = max;
   gi.min = min;
   gi.mid = lval;
   gi.init();
   gi.run();
   gi.done();
   return gi.mid;
}
