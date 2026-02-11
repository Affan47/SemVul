RenderShiftZBuffer(
                                                        vtkRenderer *renderer,
                                                        vtkActor *actor,
                                                        unsigned long typeflags,
                                                        bool forceCompileOnly)
{


  unsigned long vertFlags = typeflags & vtkPainter::VERTS;
  unsigned long lineFlags = typeflags & vtkPainter::LINES;
  unsigned long polyFlags = 0;
  int actorRep = actor->GetProperty()->GetRepresentation();
  GLint oglPolyMode[2];
  glGetIntegerv(GL_POLYGON_MODE, oglPolyMode);
  if ((actorRep == VTK_POINTS) || (oglPolyMode[0] == GL_POINT))
    {
    vertFlags |= typeflags & (vtkPainter::POLYS | vtkPainter::STRIPS);
    }
  else if ((actorRep == VTK_WIREFRAME) || (oglPolyMode[0] == GL_LINE))
    {
    lineFlags |= typeflags & (vtkPainter::POLYS | vtkPainter::STRIPS);
    }
  else
    {
    polyFlags |= typeflags & (vtkPainter::POLYS | vtkPainter::STRIPS);
    }

  GLint stackDepth, maxStackDepth;
  glGetIntegerv(GL_PROJECTION_STACK_DEPTH, &stackDepth);
  glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &maxStackDepth);


  if (stackDepth < maxStackDepth)
    {
    double range[2];
    renderer->GetActiveCamera()->GetClippingRange(range);
    if (vertFlags)
      {
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glTranslated(0.0, 0.0, 2.0*this->ZShift*(range[1]-range[0]));
      this->Superclass::RenderInternal(renderer, actor, vertFlags,
                                       forceCompileOnly);
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      }
    if (lineFlags)
      {
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glTranslated(0.0, 0.0, this->ZShift*(range[1]-range[0]));
      this->Superclass::RenderInternal(renderer, actor, lineFlags,
                                       forceCompileOnly);
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      }
    if (polyFlags)
      {
      this->Superclass::RenderInternal(renderer, actor, polyFlags,
                                       forceCompileOnly);
      }
    }
  else
    {
    this->Superclass::RenderInternal(renderer, actor, typeflags,
                                     forceCompileOnly);
    }
}
