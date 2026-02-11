main(int argc, char ** argv) {
   Fl_Window window(320,100,argv[0]);

   char buf1[100];
   Fl_Box b1(FL_DOWN_BOX,20,30,80,25,buf1);
   b1.color(FL_WHITE);
   Fl_Adjuster a1(20+80,30,3*25,25);
   a1.callback(adjcb,&b1);
   adjcb(&a1,&b1);

   char buf2[100];
   Fl_Box b2(FL_DOWN_BOX,20+80+4*25,30,80,25,buf2);
   b2.color(FL_WHITE);
   Fl_Adjuster a2(b2.x()+b2.w(),10,25,3*25);
   a2.callback(adjcb,&b2);
   adjcb(&a2,&b2);

   window.resizable(window);
   window.end();
   window.show(argc, argv);
   return Fl::run();
}
