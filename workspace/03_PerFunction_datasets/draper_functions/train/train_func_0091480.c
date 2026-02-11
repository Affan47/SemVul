trOrtho(TRcontext *tr,
             GLdouble left, GLdouble right,
             GLdouble bottom, GLdouble top,
             GLdouble zNear, GLdouble zFar)
{
   if (!tr)
      return;

   tr->Perspective = GL_FALSE;
   tr->Left = left;
   tr->Right = right;
   tr->Bottom = bottom;
   tr->Top = top;
   tr->Near = zNear;
   tr->Far = zFar;
}
