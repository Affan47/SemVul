draw(){
    Fl_Box::draw();
    double d;

    fl_push_clip(x()+5,y()+5,45,43);
    for(d=y()+5;d<95+y();d+=1.63){
      fl_begin_line();
      fl_vertex(x()+5,d);
      fl_vertex(x()+48,d);
      fl_end_line();
    }
    fl_pop_clip();

    fl_push_clip(x()+52,y()+5,45,43);
    for(d=y()+5;d<150+y();d+=2.3052){
      fl_begin_line();
      fl_vertex(x()+52,d);
      fl_vertex(x()+92,d-43);
      fl_end_line();
    }
    fl_pop_clip();

  }
