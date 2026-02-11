drawBloom(float dt) {
    if(gGourceSettings.hide_bloom) return;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_ONE, GL_ONE);

    if(!gGourceSettings.ffp) {

        bloom_shader->use();

        bloom_vbo.draw();

        glUseProgramObjectARB(0);

    } else {


        glBindTexture(GL_TEXTURE_2D, bloomtex->textureid);

        root->drawBloom(dt);
    }
}
