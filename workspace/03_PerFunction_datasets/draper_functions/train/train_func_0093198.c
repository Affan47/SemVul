Remove(wxCommandEvent& )
{
    if (nb_languages > 0)
    {
       for (int i=selected_language; i<nb_languages-1; ++i)
       {
          languages[i].name = languages[i+1].name;
          languages[i].ext = languages[i+1].ext;
          languages[i].single_line_comment = languages[i+1].single_line_comment;
          languages[i].multiple_line_comment[0] = languages[i+1].multiple_line_comment[0];
          languages[i].multiple_line_comment[1] = languages[i+1].multiple_line_comment[1];
       }
       --nb_languages;
       ReInitDialog();
    }
}
