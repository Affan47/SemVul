ajFilebuffClear(AjPFilebuff buff, ajint lines)
{
    ajint i = 0;
    AjPFilebufflist list;
    AjPFilebufflist next;
    ajint first;
    ajint ifree = 0;

    ajDebug("ajFilebuffClear (%d) Nobuff: %B size: %u\n",
            lines, buff->Nobuff, buff->Size);


    if(!buff)
        return;

    if(!buff->File)
        return;

    if(lines < 0)
        first = buff->Size;
    else
        first = buff->Pos - lines;

    if(first < 0)
        first = 0;


    if(buff->Nobuff && buff->Pos == buff->Size)

        first = buff->Pos;

    list = buff->Lines;
    for(i=0; i < first; i++)
    {

        next = list->Next;


        if(buff->Nobuff)
        {
            ajStrDel(&list->Line);
            AJFREE(list);
        }
        else
        {
            if(ajStrDelStatic(&list->Line))
            {


                ifree++;

                list->Next = NULL;

                if(!buff->Freelines)
                {

                    buff->Freelines = list;
                    buff->Freelast = list;


                }
                else
                {

                    buff->Freelast->Next = list;
                    buff->Freelast = buff->Freelast->Next;


                }
            }
            else
            {
                ajDebug("ajStrDelReuse was false\n");
            }
        }
        list = next;
    }

    buff->Pos   = 0;
    buff->Size -= i;


    buff->Lines = buff->Curr = list;


    if(buff->Nobuff && !buff->Size && lines == 1)
    {

        if(buff->Lines)
            ajFatal("Buffer error clearing unbuffered file "
                    "in ajFilebuffClear\n");

        buff->Lines = AJNEW0(buff->Last);

        ajStrAssignS(&buff->Last->Line, buff->File->Buff);
        buff->Curr = buff->Last;
        buff->Curr->Fpos = buff->Fpos;
        buff->Last->Next = NULL;
        buff->Pos = 0;
        buff->Size = 1;
    }

    return;
}
