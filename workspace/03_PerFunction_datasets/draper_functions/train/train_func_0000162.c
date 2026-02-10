getBoundingRect(const Window& wnd) const
    {
        Rect compRect;
        Rect bounds(0, 0, 0, 0);


        for(FrameList::const_iterator frame = d_frames.begin(); frame != d_frames.end(); ++frame)
        {
            compRect = (*frame).getComponentArea().getPixelRect(wnd);

            bounds.d_left   = ceguimin(bounds.d_left, compRect.d_left);
            bounds.d_top    = ceguimin(bounds.d_top, compRect.d_top);
            bounds.d_right  = ceguimax(bounds.d_right, compRect.d_right);
            bounds.d_bottom = ceguimax(bounds.d_bottom, compRect.d_bottom);
        }

        for(ImageryList::const_iterator image = d_images.begin(); image != d_images.end(); ++image)
        {
            compRect = (*image).getComponentArea().getPixelRect(wnd);

            bounds.d_left   = ceguimin(bounds.d_left, compRect.d_left);
            bounds.d_top    = ceguimin(bounds.d_top, compRect.d_top);
            bounds.d_right  = ceguimax(bounds.d_right, compRect.d_right);
            bounds.d_bottom = ceguimax(bounds.d_bottom, compRect.d_bottom);
        }

        for(TextList::const_iterator text = d_texts.begin(); text != d_texts.end(); ++text)
        {
            compRect = (*text).getComponentArea().getPixelRect(wnd);

            bounds.d_left   = ceguimin(bounds.d_left, compRect.d_left);
            bounds.d_top    = ceguimin(bounds.d_top, compRect.d_top);
            bounds.d_right  = ceguimax(bounds.d_right, compRect.d_right);
            bounds.d_bottom = ceguimax(bounds.d_bottom, compRect.d_bottom);
        }

        return bounds;
    }
