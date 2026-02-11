anim_create( SDL_Surface *gfx, int speed, int frame_w, int frame_h, SDL_Surface *surf, int x, int y )
{
    Anim *anim = calloc( 1, sizeof( Anim ) );
    if ( ( anim->img = image_create( gfx, frame_w, frame_h, surf, x, y ) ) == 0 ) {
        free( anim );
        return 0;
    }
    anim->playing = anim->loop = 0;
    anim->speed = speed;
    anim->cur_time = 0;
    anim->img->bkgnd->hide = 1;
    return anim;
}
