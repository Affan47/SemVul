portal_update_center(portal_t *portal) {
    if (portal->dir == PORTAL_DIR_VERTICAL) {
        portal->cy  = TILE_Y1(portal->s1) + portal_width(portal) * TILE_HEIGHT / 2;
    } else {
        portal->cx  = TILE_X1(portal->s1) + portal_width(portal) * TILE_WIDTH  / 2;
    }
}
