ajGraphdataAddposTextScaleC(AjPGraphdata graphdata,
                                 float x, float y,
                                 ajint colour, float scale, const char *txt)
{
    AjPGraphobj Obj;

    if(!graphdata->Dataobj)
    {
	AJNEW((graphdata->Dataobj));
	Obj = graphdata->Dataobj;
    }
    else
    {
	Obj = graphdata->Dataobj;

	while(Obj->next)
	    Obj = Obj->next;

	AJNEW(Obj->next);
	Obj = Obj->next;
    }

    ++graphdata->numofobjects;


    Obj->type = TEXT;
    Obj->text = 0;
    ajStrAssignEmptyC(&Obj->text,txt);
    Obj->xx1 = x;
    Obj->xx2 = 0.0;
    Obj->yy1 = y;
    Obj->yy2 = 0.0;
    Obj->colour = colour;
    Obj->scale = scale;
    Obj->next = 0;

    return;
}
