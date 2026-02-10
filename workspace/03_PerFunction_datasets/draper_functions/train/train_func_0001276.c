drawGL (CVector3 *z1, CVector3 *z2, CVector3 *tl, float alpha2, float lum2, bool drawlight2, bool istextured2)
{
  int i;
  CVector3 tl1;
  tl1.x = tl->x + this->tl->x;
  tl1.y = tl->y + this->tl->y;
  tl1.z = tl->z + this->tl->z;
  if (draw == 0) return;
  if (draw == 2 || gl->isSphereInFrustum (tl1.x, tl1.y, tl1.z, this->zoom * 1.5))
  {
    if (drawlight && drawlight2)
    {
      glEnable (GL_LIGHTING);
      o->draw (tl, this->tl, this->rot, this->zoom, lum * lum2, explode);
      if (refmodel != NULL)
      {
        glPushMatrix ();
        glTranslatef (tl1.x, tl1.y - 0.001 * explode * explode / timestep / timestep, tl1.z);
        glRotatef (rot->c+90, 0, -1, 0);
        glRotatef (-rot->a+90, 0, 0, 1);
        glRotatef (rot->b+180, 1, 0, 0);
        glScalef (zoom, zoom, zoom);
        if (o->refpoint)
          for (i = 0; i < numRefModels; i ++)
            if (refscale [i] > 0.001)
              refmodel [i]->draw (&o->refpoint [i / 3], &reftl [i], &refrot [i], refscale [i], lum * lum2, explode);
        glPopMatrix ();
      }
    }
    else
    {
      glDisable (GL_LIGHTING);
      if (istextured2)
      {
        o->draw2 (tl, this->tl, this->rot, this->zoom, explode);
      }
      else
      {
        if (drawlight2)
          o->draw3 (tl, this->tl, this->rot, this->zoom, lum * lum2, explode);
        else
          o->draw3 (tl, this->tl, this->rot, this->zoom, explode);
      }
    }
  }
}
