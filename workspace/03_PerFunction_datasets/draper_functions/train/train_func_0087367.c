deliver_index(FILE *fout, struct chmFile *file)
{
    fprintf(fout,
            "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"

            "Content-Type: text/html\r\n\r\n"

            "<h2><u>CHM contents:</u></h2>"
            "<body><table>"
            "<tr><td><h5>Size:</h5></td><td><h5>File:</h5></td></tr>"
            "<tt>");
    if (! chm_enumerate(file, CHM_ENUMERATE_ALL, _print_ui_index, fout))
        fprintf(fout,"<br>   *** ERROR ***\r\n");
    fprintf(fout,"</tt> </table></body></html>");
}
