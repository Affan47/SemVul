DrawTubeList(Tube *root, Tube *current_tube, GLint s, GLint r) {

  GLfloat red_color[] = {0.8, 0.1, 0.1, 1.0};
  GLfloat gray_color[] = {0.8, 0.9, 0.9, 0.9};

  if(root != NULL) {

    glPushMatrix();
    if(current_tube == root)
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red_color);
    else
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray_color);
    glRotatef(180,1.0,0.0,0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    DrawTube(root, s, r);
    glPopMatrix();
    DrawTubeList(root->next, current_tube, s, r);

  }

}
