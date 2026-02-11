vocfnw(voccxdef *voccx, vocseadef *search_ctx)
{
    vocdef  *v, *vf;
    vocwdef *vw, *vwf;
    vocdef  *c = search_ctx->v;
    int      first;


    first = TRUE;
    vw = vocwget(voccx, search_ctx->vw->vocwnxt);


    for (v = c, vf = 0 ; v != 0 && vf == 0 ; v = v->vocnxt, first = FALSE)
    {

        if (first
            || (voceq(search_ctx->wrd1, search_ctx->len1,
                      v->voctxt, v->voclen)
                && voceq(search_ctx->wrd2, search_ctx->len2,
                         v->voctxt + v->voclen, v->vocln2)))
        {


            if (!first)
                vw = vocwget(voccx, v->vocwlst);


            for ( ; vw ; vw = vocwget(voccx, vw->vocwnxt))
            {
                if (search_ctx->vw->vocwtyp == vw->vocwtyp
                    && !(vw->vocwflg & VOCFCLASS)
                    && !(vw->vocwflg & VOCFDEL))
                {


                    vf = v;
                    vwf = vw;
                    break;
                }
            }
        }
    }


    search_ctx->v = vf;
    search_ctx->vw = (vf ? vwf : 0);
    return(search_ctx->vw);
}
