charge_recette(int debut,int fin)
{
    GtkTextIter iter1, iter2;
    gchar *utf8_buf;

    char buf[BUFSIZE];


     fseek(fp,0,0);

    gtk_text_buffer_get_start_iter(buffer, &iter1);
    gtk_text_buffer_get_end_iter(buffer, &iter2);
    gtk_text_buffer_delete(buffer, &iter1, &iter2);


     fseek(fp,debut,0);
    gsize bytes_read, bytes_written;
    GIConv convert;

     convert = g_iconv_open("UTF8", "ISO8859-1");
     while (ftell(fp) < fin)
     {
      fgets(buf,BUFSIZE,fp);
      utf8_buf = g_convert_with_iconv(buf, -1, convert, &bytes_read, &bytes_written, NULL);


      gtk_text_buffer_get_end_iter(buffer, &iter2);
      gtk_text_buffer_insert(buffer, &iter2, utf8_buf, -1);
     }
     g_iconv_close(convert);
}
