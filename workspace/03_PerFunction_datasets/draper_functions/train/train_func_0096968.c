ajFeatNew(AjPFeattable thys,
		     const AjPStr source,
		     const AjPStr type,
		     ajint Start, ajint End,
		     float score,
		     char  strand,
		     ajint frame)
{
    ajuint flags    = 0;
    AjPFeature ret = NULL;

    if(ajStrMatchC(thys->Type, "P"))
        ret = ajFeatNewProtFlags(thys,source,type,Start,End,score,flags);
    else
        ret = ajFeatNewNucFlags(thys,source,type,Start,End,score,strand,frame,
                                0,0,0,NULL, NULL,flags);

    return ret;
}
