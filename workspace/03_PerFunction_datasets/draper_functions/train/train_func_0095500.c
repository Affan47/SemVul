draw() {
    if(isFinished()) return;


    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0f, 0.0f, 0.0f, alpha * 0.333f);

    glPushMatrix();
        glTranslatef(shadow.x, shadow.y, 0.0f);

        glBegin(GL_QUADS);
            glVertex2f(pos.x,       pos.y);
            glVertex2f(pos.x,       pos.y + height);
            glVertex2f(pos.x+width, pos.y + height);
            glVertex2f(pos.x+width, pos.y);
        glEnd();
    glPopMatrix();

    glBegin(GL_QUADS);
        glColor4f(colour.x * 0.5f, colour.y * 0.5f, colour.z * 0.5f, alpha);
        glVertex2f(pos.x,         pos.y);
        glVertex2f(pos.x,         pos.y + height);
        glColor4f(colour.x, colour.y, colour.z, alpha);
        glVertex2f(pos.x + width, pos.y + height);
        glVertex2f(pos.x + width, pos.y);
    glEnd();

    glEnable(GL_TEXTURE_2D);

    font.setColour(vec4(1.0f, 1.0f, 1.0f, alpha));

    font.dropShadow(false);
    font.draw((int)pos.x+2, (int)pos.y+3,  display_ext.c_str());

    font.dropShadow(true);
    font.print((int)pos.x+width+4, (int)pos.y+3, "%d", count);
}
