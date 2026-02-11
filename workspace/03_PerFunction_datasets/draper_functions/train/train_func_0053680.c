writeNativeFormat(std::ostream &os, char *comments) {
   int depth = node_depth(root) ;
   os << "[M2] (golly " STRINGIFY(VERSION) ")\n" ;


   os << "#R " << hliferules.getrule() << '\n' ;

   if (generation > bigint::zero) {

      os << "#G " << generation.tostring('\0') << '\n' ;
   }
   if (comments && comments[0]) {

      os << comments;
   }
   inGC = 1 ;


   cellcounter = 0 ;
   vector<int> depths(timeline.framecount) ;
   int framestosave = timeline.framecount ;
   if (timeline.savetimeline == 0)
     framestosave = 0 ;
   if (framestosave) {
     for (int i=0; i<timeline.framecount; i++) {
       node *frame = (node*)timeline.frames[i] ;
       depths[i] = node_depth(frame) ;
     }
     for (int i=0; i<timeline.framecount; i++) {
       node *frame = (node*)timeline.frames[i] ;
       writecell_2p1(frame, depths[i]) ;
     }
   }
   writecell_2p1(root, depth) ;
   writecells = cellcounter ;
   cellcounter = 0 ;
   if (framestosave) {
      os << "#FRAMES"
         << ' ' << timeline.framecount
         << ' ' << timeline.start.tostring()
         << ' ' << timeline.base << '^' << timeline.expo << '\n' ;
     for (int i=0; i<timeline.framecount; i++) {
       node *frame = (node*)timeline.frames[i] ;
       writecell_2p2(os, frame, depths[i]) ;
       os << "#FRAME " << i << ' ' << (g_uintptr_t)frame->next << '\n' ;
     }
   }
   writecell_2p2(os, root, depth) ;

   if (framestosave) {
     for (int i=0; i<timeline.framecount; i++) {
       node *frame = (node*)timeline.frames[i] ;
       aftercalcpop2(frame, depths[i], 0) ;
     }
   }
   aftercalcpop2(root, depth, 0) ;
   inGC = 0 ;
   return 0 ;
}
