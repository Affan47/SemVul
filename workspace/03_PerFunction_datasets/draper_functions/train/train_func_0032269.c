positionSelf(void)
    {

        if (d_inPositionSelf)
            return;

        d_inPositionSelf = true;

        MouseCursor& cursor = MouseCursor::getSingleton();
        Rect screen(Vector2(0, 0), System::getSingleton().getRenderer()->getDisplaySize());
        Rect tipRect(getUnclippedOuterRect());
        const Image* mouseImage = cursor.getImage();

        Point mousePos(cursor.getPosition());
        Size mouseSz(0,0);

        if (mouseImage)
        {
            mouseSz = mouseImage->getSize();
        }

        Point tmpPos(mousePos.d_x + mouseSz.d_width, mousePos.d_y + mouseSz.d_height);
        tipRect.setPosition(tmpPos);


        if (screen.d_right < tipRect.d_right)
        {
            tmpPos.d_x = mousePos.d_x - tipRect.getWidth() - 5;
        }


        if (screen.d_bottom < tipRect.d_bottom)
        {
            tmpPos.d_y = mousePos.d_y - tipRect.getHeight() - 5;
        }


        setPosition(
            UVector2(cegui_absdim(tmpPos.d_x),
                     cegui_absdim(tmpPos.d_y)));

        d_inPositionSelf = false;
    }
