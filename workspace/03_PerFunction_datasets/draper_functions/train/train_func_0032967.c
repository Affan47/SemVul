Sprite_setAnimation( Sprite *s, Animation anim ) {
    s->animation = AnimManager_get( &game->anims, anim );


    if( s->used_sprite >= 0 ) {
        Scene_modifySprite( game->scene, s->used_sprite, SA_Animation, s->animation );
    }
}
