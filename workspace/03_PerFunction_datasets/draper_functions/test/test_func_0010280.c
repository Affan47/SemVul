makeSprite (const char type, int i, int j)
{
    int spriteId;
    KGrSprite * sprite = m_renderer->getSpriteItem (type, TickTime);

    if (m_sprites.count(0) > 0 &&
        ((spriteId = m_sprites.lastIndexOf (0)) >= 0)) {

        m_sprites[spriteId] = sprite;
    }
    else {

        spriteId = m_sprites.count();
        m_sprites.append (sprite);
    }

    int frame1 = animationStartFrames [FALL_L];

    switch (type) {
    case HERO:
        m_heroId = spriteId;
        sprite->setZ (1);
        break;
    case ENEMY:
        sprite->setZ (2);
        break;
    case BRICK:
        frame1 = animationStartFrames [OPEN_BRICK];


        sprite->setZ (0);


        paintCell (i, j, FREE);
        break;
    default:
        break;
    }

    sprite->setFrame (frame1);
    sprite->setCoordinateSystem (m_topLeftX, m_topLeftY, m_tileSize);
    addItem (sprite);
    sprite->move (i, j, frame1);
    return spriteId;
}
