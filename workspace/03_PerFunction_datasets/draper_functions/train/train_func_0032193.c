TXT_SpinControlKeyPress(TXT_UNCAST_ARG(spincontrol), int key)
{
    TXT_CAST_ARG(txt_spincontrol_t, spincontrol);


    if (spincontrol->editing)
    {
        if (key == KEY_ENTER)
        {
            FinishEditing(spincontrol);
            return 1;
        }

        if (key == KEY_ESCAPE)
        {

            spincontrol->editing = 0;
            return 1;
        }

        if (isdigit(key) || key == '-' || key == '.')
        {
            AddCharacter(spincontrol, key);
            return 1;
        }

        if (key == KEY_BACKSPACE)
        {
            Backspace(spincontrol);
            return 1;
        }
    }
    else
    {


        if (key == KEY_ENTER)
        {
            spincontrol->editing = 1;
            strcpy(spincontrol->buffer, "");
            return 1;
        }
        if (key == KEY_LEFTARROW)
        {
            switch (spincontrol->type)
            {
                case TXT_SPINCONTROL_INT:
                    spincontrol->value->i -= spincontrol->step.i;
                    break;

                case TXT_SPINCONTROL_FLOAT:
                    spincontrol->value->f -= spincontrol->step.f;
                    break;
            }

            EnforceLimits(spincontrol);

            return 1;
        }

        if (key == KEY_RIGHTARROW)
        {
            switch (spincontrol->type)
            {
                case TXT_SPINCONTROL_INT:
                    spincontrol->value->i += spincontrol->step.i;
                    break;

                case TXT_SPINCONTROL_FLOAT:
                    spincontrol->value->f += spincontrol->step.f;
                    break;
            }

            EnforceLimits(spincontrol);

            return 1;
        }
    }

    return 0;
}
