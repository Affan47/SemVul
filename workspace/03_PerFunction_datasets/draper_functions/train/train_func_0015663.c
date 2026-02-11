submit ()
{
  Ekiga::FormBuilder builder;

  gtk_widget_hide (GTK_WIDGET (window));

  for (std::list<Submitter *>::iterator iter = submitters.begin ();
       iter != submitters.end ();
       iter++)
    (*iter)->submit (builder);

  request->submit (builder);
}
