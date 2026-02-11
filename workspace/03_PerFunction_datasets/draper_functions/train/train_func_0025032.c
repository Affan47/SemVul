doActiveState(float elapsed)
    {

        if (!d_target || d_target->getTooltipText().empty())
        {
            switchToInactiveState();
        }

        else if ((d_displayTime > 0) && ((d_elapsed += elapsed) >= d_displayTime))
        {

            switchToFadeOutState();
        }
    }
