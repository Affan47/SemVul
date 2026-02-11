wipe_engr_at(xchar x, xchar y, xchar cnt)
{
    struct engr *ep = engr_at(x,y);


    if(ep && ep->engr_type != HEADSTONE){
        if(ep->engr_type != BURN || is_ice(x,y)) {
            if(ep->engr_type != DUST && ep->engr_type != ENGR_BLOOD) {
                cnt = rn2(1 + 50/(cnt+1)) ? 0 : 1;
            }
            wipeout_text(ep->engr_txt, (int)cnt, 0);
            while(ep->engr_txt[0] == ' ')
                    ep->engr_txt++;
            if(!ep->engr_txt[0]) del_engr(ep);
        }
    }
}
