draw (s_int16 x, s_int16 y, s_int16 sx, s_int16 sy, u_int16 sl,
                    u_int16 sh, const drawing_area * da_opt,
                    surface * target) const
{
    if (target == NULL) target = &screen::display;

    setup_rects (x, y, sx, sy, sl, sh, da_opt);

    if (screen::dbl_mode())
    {
        x <<= 1;
        y <<= 1;
        sx <<= 1;
        sy <<= 1;
        sl <<= 1;
        sh <<= 1;
        srcrect.x <<= 1;
        srcrect.y <<= 1;
        srcrect.w <<= 1;
        srcrect.h <<= 1;
        dstrect.x <<= 1;
        dstrect.y <<= 1;
        dstrect.w <<= 1;
        dstrect.h <<= 1;
    }

    if (!dstrect.w || !dstrect.h)
        return;

    if (changed)
    {
        changed = false;
        if (is_masked ())
            SDL_SetColorKey (vis, SDL_SRCCOLORKEY | SDL_RLEACCEL, screen::trans_col ());
        else
            SDL_SetColorKey (vis, 0, 0);
    }

    if (alpha () != 255)
        SDL_SetAlpha (vis, SDL_SRCALPHA, alpha_);

    SDL_BlitSurface (vis, &srcrect, target->vis, &dstrect);
    target->changed = true;
}
