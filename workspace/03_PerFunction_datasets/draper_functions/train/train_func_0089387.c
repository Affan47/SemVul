eventMouseMotion (const SDL_MouseMotionEvent *button)
{
   MapCoordinate mc = screenPos2mapPos( SPoint(button->x, button->y));
   if ( !(mc.valid() && mc.x < actmap->xsize && mc.y < actmap->ysize ))
      return false;

   if ( button->type == SDL_MOUSEMOTION && (button->state == SDL_BUTTON( CGameOptions::Instance()->mouse.fieldmarkbutton) )) {
      bool changed = cursor.pos() != mc;
      if ( changed ) {
         MapCoordinate oldpos = cursor.pos();
         cursor.pos() = mc;
         cursor.invisible = 0;
         dirty = Curs;

         redrawMapAtCursor( oldpos );
         cursorMoved();

         mouseDraggedToField( mc, SPoint(button->x, button->y), changed, signalPrio );

         return true;
     }
   }
   return false;
}
