draw ( const std::list<Magick::Drawable> &drawable_ )
{
  modifyImage();

  DrawingWand *wand = DrawAllocateWand( options()->drawInfo(), image());

  if(wand)
    {
      for( std::list<Magick::Drawable>::const_iterator p = drawable_.begin();
           p != drawable_.end(); p++ )
        {
          p->operator()(wand);
          if( constImage()->exception.severity != UndefinedException)
            break;
        }

      if( constImage()->exception.severity == UndefinedException)
        DrawRender(wand);

      wand=DestroyDrawingWand(wand);
    }

  throwImageException();
}
