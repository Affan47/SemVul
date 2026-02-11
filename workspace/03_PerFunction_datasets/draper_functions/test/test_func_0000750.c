MultiListBox (PG_Widget *parent, const PG_Rect &r ) : PG_Widget( parent, r )
{
   SetTransparency( 255 );

   listbox = new PG_ListBox( parent, PG_Rect( r.x, r.y, r.w, r.h - 30 ) );
   listbox->SetMultiSelect( true );

   (new PG_Button( parent, PG_Rect( r.x, r.y + r.h - 25, r.w/2-5, 25 ), "All"))->sigClick.connect( SigC::slot( *this, &MultiListBox::all ));
   (new PG_Button( parent, PG_Rect( r.x + r.w/2 + 5, r.y + r.h - 25, r.w/2-5, 25 ), "None"))->sigClick.connect( SigC::slot( *this, &MultiListBox::none ));
}
