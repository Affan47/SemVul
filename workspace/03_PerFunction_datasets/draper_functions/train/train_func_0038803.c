updateHeading(void)
{
  if (table()!=0)
   {
     if (table()->firstMap()==MSTrue&&table()->frozen()==MSFalse)
      {
        int hh=table()->headingsHeight();
        table()->calculateHeadingsHeight();
        if (hh!=table()->headingsHeight())
         {
           table()->adjustNumVisible();
           table()->redraw();
         }
        else table()->updateColumnHeadings();
      }
   }
}
