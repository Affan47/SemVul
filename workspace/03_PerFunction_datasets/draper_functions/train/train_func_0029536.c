deftags_stuff(zdialog *zd)
{
   GtkWidget      *widget;
   GtkTextBuffer  *textbuff;
   GtkTextIter    iter1, iter2;
   int            ii, cc;
   char           catgname[tagcc+3];
   char           *pp1, *pp2;

   widget = zdialog_widget(zd,"deftags");
   wclear(widget);

   for (ii = 0; ii < maxtagcats; ii++)
   {
      pp1 = tags_deftags[ii];
      if (! pp1) break;
      pp2 = strchr(pp1,':');
      if (! pp2) continue;
      if (pp2 > pp1 + tagcc-3) continue;
      pp2 += 2;
      cc = pp2 - pp1 + 1;
      strncpy0(catgname,pp1,cc);
      wprintx(widget,0,catgname,"monospace bold 9");
      if (*pp2) wprintx(widget,0,pp2,"monospace 9");
      wprintx(widget,0,"\n");
   }

   textbuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
   gtk_text_buffer_get_bounds(textbuff,&iter1,&iter2);
   pp1 = gtk_text_buffer_get_text(textbuff,&iter1,&iter2,0);
   strncpy0(tags_deftext,pp1,tagTcc);

   return;
}
