FindFileLines (EBuffer *B) {
    char path[MAXPATH];
    char *pos;
    strcpy (path,Directory);Slash (path,1);pos=path+strlen (path);
    for (int i=0;i<LineCount;i++)
        if (Lines[i]->Buf==0&&Lines[i]->File!=0) {
            strcpy (pos,Lines[i]->File);
            if (filecmp (B->FileName,path)==0) {
                AssignBuffer (B,i);
            }
        }
}
