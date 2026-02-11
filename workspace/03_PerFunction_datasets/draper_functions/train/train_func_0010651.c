AddLine (const char *file, int line, const char *msg, int status) {
    SvnLine *l;

    l=(SvnLine *)malloc (sizeof (SvnLine));
    if (l!=0) {
        l->File=file?strdup (file):0;
        l->Line=line;
        l->Msg=msg?strdup (msg):0;
        l->Buf=0;
        l->Status = (char)status;

        LineCount++;
        Lines=(SvnLine **)realloc (Lines,sizeof (SvnLine *)*LineCount);
        Lines[LineCount-1]=l;
        FindBuffer (LineCount-1);

        UpdateList ();
    }
}
