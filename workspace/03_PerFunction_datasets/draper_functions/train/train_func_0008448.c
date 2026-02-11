put(int ch) throw(StreamException)
{
    if (closed)
        return;

    unsigned char uch;
    gunichar gch;

    switch (scheme) {

        case SCHEME_FILE:
            if (!outf)
                return;
            uch = (unsigned char)(ch & 0xff);
            if (fputc(uch, outf) == EOF) {
                Glib::ustring err = "ERROR writing to file ";
                throw StreamException(err);
            }

        break;

        case SCHEME_DATA:
            gch = (gunichar) ch;
            data.push_back(gch);
        break;

    }

}
