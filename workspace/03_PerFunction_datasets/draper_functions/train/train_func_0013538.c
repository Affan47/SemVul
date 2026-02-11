init( const char* _title, const char* text , int xx1 , int yy1  , int xxsize , int yysize  )
{


   tdialogbox::init();
   x1 = xx1;
   y1 = yy1;
   xsize = xxsize;
   ysize = yysize;
   textstart = 42 ;
   textsizey = (ysize - textstart - 40);
   starty = starty + 10;
   title = _title;
   windowstyle ^= dlg_in3d;
   action=0;


   txt = text;

   setparams ( x1 + 13, y1 + textstart, x1 + xsize - 41, y1 + ysize - 40, txt, black, dblue);
   addbutton ( "~O~K", 10, ysize - 30, xsize - 10, ysize - 10, 0, 1, 10, true );
   addkey ( 10, ct_space );
   addkey ( 10, ct_enter );
   addkey ( 10, ct_esc );
   tvt_dispactive = 0;
   displaytext(  );
   textsizeycomplete = tvt_yp;
   tvt_dispactive = 1;


   if (textsizeycomplete >= textsizey) {
      scrollbarvisible = true;

      addscrollbar(xsize - 30,starty,xsize - 15,ysize - 35,&textsizeycomplete, textsizey, &tvt_starty,1,0);
      setscrollspeed ( 1 , 1 );

      rightspace = 40;
   }
   else {
      rightspace = 10;
      scrollbarvisible = false;
   }

   tvt_starty = 0;
   buildgraphics();
}
