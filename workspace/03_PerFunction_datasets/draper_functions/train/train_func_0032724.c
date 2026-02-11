drawFiles(float dt) {
    if(gGourceSettings.hide_files) return;


    if(trace_debug) {
        glDisable(GL_TEXTURE_2D);
    } else {
        glEnable(GL_TEXTURE_2D);
    }

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(!gGourceSettings.ffp) {
        glBindTexture(GL_TEXTURE_2D, gGourceSettings.file_graphic->textureid);

        file_vbo.draw();
    } else {
        root->drawFiles(dt);
    }
}
