parse_debug(char string[]) {

   const char * ptr;
   int value;
   int depth;
   int node_nb;
   int time;
   int inc;


   ptr = strtok(string," ");

   for (ptr = strtok(NULL," "); ptr != NULL; ptr = strtok(NULL," ")) {

      if (false) {

      } else if (string_equal(ptr,"perft")) {

         ptr = strtok(NULL," ");
         if (ptr == NULL) my_fatal("parse_debug(): missing argument\n");

         value = atoi(ptr);
         ASSERT(value>0&&value<DepthMax);

         init();
         perft(value);

      } else if (string_equal(ptr,"bench")) {

         ptr = strtok(NULL," ");
         if (ptr == NULL) my_fatal("parse_debug(): missing argument\n");

         value = atoi(ptr);
         ASSERT(value>0&&value<DepthMax);

         init();
         bench(value);

      } else if (string_equal(ptr,"match")) {

         ptr = strtok(NULL," ");
         if (ptr == NULL) my_fatal("parse_debug(): missing argument\n");

         depth = atoi(ptr);
         ASSERT(depth>=0&&depth<DepthMax);

         ptr = strtok(NULL," ");
         if (ptr == NULL) my_fatal("parse_debug(): missing argument\n");

         node_nb = atoi(ptr);
         ASSERT(node_nb>=0);

         ptr = strtok(NULL," ");
         if (ptr == NULL) my_fatal("parse_debug(): missing argument\n");

         time = atoi(ptr);
         ASSERT(time>=0);

         ptr = strtok(NULL," ");
         if (ptr == NULL) my_fatal("parse_debug(): missing argument\n");

         inc = atoi(ptr);
         ASSERT(inc>=0);

         init();
         match(depth,node_nb,time,inc);
      }
   }
}
