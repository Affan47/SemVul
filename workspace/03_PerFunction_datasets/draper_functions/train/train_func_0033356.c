handleFontSelection (const EventArgs& e)
    {

        Listbox *lbox = static_cast<Listbox*> (
            static_cast<const WindowEventArgs&> (e).window);

        if (lbox->getFirstSelectedItem ())
		{
            Font *font = &FontManager::getSingleton ().get(
                lbox->getFirstSelectedItem ()->getText ());


            WindowManager& winMgr = WindowManager::getSingleton ();
            winMgr.getWindow("FontDemo/FontSample")->setFont (font);

            bool b = font->isPropertyPresent ("AutoScaled");
            Checkbox *cb = static_cast<Checkbox *> (winMgr.getWindow("FontDemo/AutoScaled"));
            cb->setEnabled (b);
            if (b)
                cb->setSelected (PropertyHelper::stringToBool (font->getProperty ("AutoScaled")));

            b = font->isPropertyPresent ("Antialiased");
            cb = static_cast<Checkbox *> (winMgr.getWindow("FontDemo/Antialiased"));
            cb->setEnabled (b);
            if (b)
                cb->setSelected (PropertyHelper::stringToBool (font->getProperty ("Antialiased")));

            b = font->isPropertyPresent ("PointSize");
            Scrollbar *sb = static_cast<Scrollbar *> (
                winMgr.getWindow("FontDemo/PointSize"));
            sb->setEnabled (b);


			if (font->isPropertyPresent("PointSize"))
				font->setProperty ("PointSize",
                        PropertyHelper::intToString (
                            int (MIN_POINT_SIZE + sb->getScrollPosition ())));

            setFontDesc ();
		}

        return true;
    }
